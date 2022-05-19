﻿#include "IV8.h"
#include "V8PCH.h"

PRAGMA_DISABLE_SHADOW_VARIABLE_WARNINGS

#include <libplatform/libplatform.h>
#include "JavascriptContext.h"
#include "JavascriptStats.h"
#include "JavascriptSettings.h"
#include "Containers/Ticker.h"
#include "Containers/Queue.h"
#include "Misc/Paths.h"
#include "UObject/UObjectIterator.h"
#include "UObject/UObjectGlobals.h"
#include "HAL/FileManagerGeneric.h"

DEFINE_STAT(STAT_V8IdleTask);
DEFINE_STAT(STAT_JavascriptDelegate);
DEFINE_STAT(STAT_JavascriptProxy);
DEFINE_STAT(STAT_Scavenge);
DEFINE_STAT(STAT_MarkSweepCompact);
DEFINE_STAT(STAT_IncrementalMarking);
DEFINE_STAT(STAT_ProcessWeakCallbacks);

DEFINE_STAT(STAT_JavascriptPropertyGet);
DEFINE_STAT(STAT_JavascriptPropertySet);
DEFINE_STAT(STAT_JavascriptFunctionCallToEngine);
DEFINE_STAT(STAT_JavascriptFunctionCallToJavascript);
DEFINE_STAT(STAT_JavascriptReadOffStruct);

DEFINE_STAT(STAT_NewSpace);
DEFINE_STAT(STAT_OldSpace);
DEFINE_STAT(STAT_CodeSpace);
DEFINE_STAT(STAT_MapSpace);
DEFINE_STAT(STAT_LoSpace);

using namespace v8;

static float GV8IdleTaskBudget = 1 / 60.0f;

UJavascriptSettings::UJavascriptSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	V8Flags = TEXT("--harmony --harmony-shipping --es-staging --expose-gc");
}

void UJavascriptSettings::Apply() const
{
	IV8::Get().SetFlagsFromString(V8Flags);
}

class FUnrealJSPlatform : public v8::Platform
{
private:
	std::unique_ptr<v8::Platform> platform_;
	TQueue<v8::IdleTask*> IdleTasks;
	FTickerDelegate TickDelegate;
	FDelegateHandle TickHandle;
	bool bActive{ true };

public:
	v8::Platform* platform() const
	{
		return platform_.get();
	}
	FUnrealJSPlatform() 
		: platform_(platform::NewDefaultPlatform(0, platform::IdleTaskSupport::kEnabled))
	{
		TickDelegate = FTickerDelegate::CreateRaw(this, &FUnrealJSPlatform::HandleTicker);
		TickHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
	}

	~FUnrealJSPlatform()
	{
		FTicker::GetCoreTicker().RemoveTicker(TickHandle);
		platform_.release();
	}

	void Shutdown()
	{
		bActive = false;
		RunIdleTasks(FLT_MAX);
	}
	virtual int NumberOfWorkerThreads() { return platform_->NumberOfWorkerThreads(); }

	virtual std::shared_ptr<v8::TaskRunner> GetForegroundTaskRunner(Isolate* isolate)
	{
		return platform_->GetForegroundTaskRunner(isolate);
	}

	virtual void CallOnForegroundThread(Isolate* isolate, Task* task)
	{
		platform_->CallOnForegroundThread(isolate, task);
	}

	virtual void CallOnWorkerThread(std::unique_ptr<Task> task)
	{
		platform_->CallOnWorkerThread(std::move(task));
	}

	virtual void CallDelayedOnWorkerThread(std::unique_ptr<Task> task,
		double delay_in_seconds)
	{
		platform_->CallOnWorkerThread(std::move(task));
	}

	virtual void CallDelayedOnForegroundThread(Isolate* isolate, Task* task,
		double delay_in_seconds)
	{
		platform_->CallOnForegroundThread(isolate, task);
	}

	virtual void CallIdleOnForegroundThread(Isolate* isolate, IdleTask* task) 
	{
		IdleTasks.Enqueue(task);
	}

	virtual bool IdleTasksEnabled(Isolate* isolate) 
	{
		return bActive;
	}

	virtual double MonotonicallyIncreasingTime()
	{
		return platform_->MonotonicallyIncreasingTime();
	}

#if V8_MAJOR_VERSION > 5 && V8_MINOR_VERSION > 3
	virtual double CurrentClockTimeMillis()
	{
		return platform_->CurrentClockTimeMillis();
	}
#endif

#if V8_MAJOR_VERSION > 5
	v8::TracingController* GetTracingController() override
	{
		return platform_->GetTracingController();
	}
#endif

	void RunIdleTasks(float Budget)
	{
		float Start = FPlatformTime::Seconds();
		while (!IdleTasks.IsEmpty() && Budget > 0)
		{
			v8::IdleTask* Task = nullptr;
			IdleTasks.Dequeue(Task);

			{
				SCOPE_CYCLE_COUNTER(STAT_V8IdleTask);

				Task->Run(MonotonicallyIncreasingTime() + Budget);
			}
			
			delete Task;
			
			float Now = FPlatformTime::Seconds();
			float Elapsed = Now - Start;
			Start = Now;
			Budget -= Elapsed;
		}
	}

	bool HandleTicker(float DeltaTime)
	{	
		RunIdleTasks(FMath::Max<float>(0, GV8IdleTaskBudget - DeltaTime));
		return true;
	}
};

class FV8Module : public IV8
{
public:
	TArray<FString> Paths;
	FUnrealJSPlatform platform_;

	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		//Game folder should tak precedence
		Paths.Add(GetGameScriptsDirectory());
		//@HACK : Dirty hacks
		
		//project plugins
		AddAllPluginContentScriptPaths(Paths);

		//engine unreal.js possible plugin locations
		Paths.Add(GetPluginScriptsDirectory());
		Paths.Add(GetPluginScriptsDirectory2());
		Paths.Add(GetPluginScriptsDirectory3());
		
		Paths.Add(GetPakPluginScriptsDirectory());

		const UJavascriptSettings& Settings = *GetDefault<UJavascriptSettings>();
		Settings.Apply();

		FCoreUObjectDelegates::GetPreGarbageCollectDelegate().AddRaw(this, &FV8Module::OnPreGarbageCollection);

		V8::InitializeICUDefaultLocation(nullptr);
		V8::InitializePlatform(&platform_);
		V8::Initialize();

		FName NAME_JavascriptCmd("JavascriptCmd");
		GLog->Log(NAME_JavascriptCmd, ELogVerbosity::Log, *FString::Printf(TEXT("Unreal.js started. V8 %d.%d.%d"), V8_MAJOR_VERSION, V8_MINOR_VERSION, V8_BUILD_NUMBER));
	}

	virtual void ShutdownModule() override
	{
		FCoreUObjectDelegates::GetPreGarbageCollectDelegate().RemoveAll(this);

		platform_.Shutdown();

		V8::Dispose();
		V8::ShutdownPlatform();
	}

	//@HACK
	static FString GetPluginScriptsDirectory()
	{
		return FPaths::EnginePluginsDir() / "Backend/UnrealJS/Content/Scripts/";
	}

	static FString GetPluginScriptsDirectory2()
	{
		return FPaths::EnginePluginsDir() / "UnrealJS/Content/Scripts/";
	}

	static FString GetPluginScriptsDirectory3()
	{
		return FPaths::EnginePluginsDir() / "Marketplace/UnrealJS/Content/Scripts/";
	}

	static FString GetPluginScriptsDirectory4()
	{
		return FPaths::ProjectPluginsDir() / "UnrealJS/Content/Scripts/";
	}

	//git clones project plugin
	static FString GetPluginScriptsDirectory5()
	{
		return FPaths::ProjectPluginsDir() / "Unreal.js-core/Content/Scripts/";
	}

	//Packaged with plugin scripts copied to project for e.g. android
	static FString GetPluginScriptsDirectory6()
	{
		return FPaths::ProjectDir() / "/Content/Scripts/UnrealJSPlugin/";
	}

	static TArray<FString>SubPaths(const FString& Directory)
	{
		TArray<FString> FoundFolders;
		if (FPaths::DirectoryExists(Directory))
		{
			FFileManagerGeneric::Get().FindFilesRecursive(FoundFolders, *Directory, TEXT("*"), false, true, true);
		}
		return FoundFolders;
	}

	static TArray<FString> ValidSubPaths(const FString& Directory) 
	{
		TArray<FString> AllSubFolders = SubPaths(Directory);
		TArray<FString> ValidFolders;
		for (int i = 0; i < AllSubFolders.Num(); i++)
		{
			if (AllSubFolders[i].EndsWith(TEXT("Content/Scripts")))
			{
				ValidFolders.Add(AllSubFolders[i]);
				UE_LOG(LogTemp, Warning, TEXT("Found Folder: %s"), *AllSubFolders[i]);
			}
		}
		return ValidFolders;
	}

	//optional variant of 5
	static void AddAllPluginContentScriptPaths(TArray<FString>& InOutPaths)
	{
		TArray<FString> NewPaths = ValidSubPaths(FPaths::ProjectPluginsDir());

		InOutPaths.Append(NewPaths);
	}

	static FString GetPakPluginScriptsDirectory()
	{
		return FPaths::EngineDir() / "Contents/Scripts/";
	}

	static FString GetGameScriptsDirectory()
	{
		return FPaths::ProjectContentDir() / "Scripts/";
	}

	virtual void AddGlobalScriptSearchPath(const FString& Path) override
	{
		Paths.Add(Path);
	}

	virtual void RemoveGlobalScriptSearchPath(const FString& Path) override
	{
		Paths.Remove(Path);
	}

	virtual TArray<FString> GetGlobalScriptSearchPaths() override
	{
		return Paths;
	}

	virtual void FillAutoCompletion(TSharedPtr<FString> TargetContext, TArray<FString>& OutArray, const TCHAR* Input) override
	{
		static const TCHAR* SourceCode = (const TCHAR *)LR"doc(
(function () {
    var pattern = '{0}'; var head = '';
    pattern.replace(/\\W*([\\w\\.]+)$/, function (a, b, c) { head = pattern.substr(0, c + a.length - b.length); pattern = b });
    var index = pattern.lastIndexOf('.');
    var scope = this;
    var left = '';
    if (index >= 0) {
        left = pattern.substr(0, index + 1);
        try { scope = eval(pattern.substr(0, index)); }
        catch (e) { scope = null; }
        pattern = pattern.substr(index + 1);
    }
    result = [];
    for (var k in scope) {
        if (k.indexOf(pattern) == 0) {
            result.push(head + left + k);
        }
    }
    return result.join(',');
})()
)doc";

		for (TObjectIterator<UJavascriptContext> It; It; ++It)
		{
			UJavascriptContext* Context = *It;

			if (Context->ContextId == TargetContext || (!TargetContext.IsValid() && Context->IsDebugContext()))
			{
				FString Result = Context->RunScript(FString::Format(SourceCode, { FString(Input).ReplaceCharWithEscapedChar() }), false);
				Result.ParseIntoArray(OutArray, TEXT(","));
			}
		}
	}

	virtual void Exec(TSharedPtr<FString> TargetContext, const TCHAR* Command) override
	{
		for (TObjectIterator<UJavascriptContext> It; It; ++It)
		{
			UJavascriptContext* Context = *It;

			if (Context->ContextId == TargetContext || (!TargetContext.IsValid() && Context->IsDebugContext()))
			{
				static FName NAME_JavascriptCmd("JavascriptCmd");
				GLog->Log(NAME_JavascriptCmd, ELogVerbosity::Log, Command);
				Context->RunScript(Command);
			}
		}
	}

	virtual bool HasDebugContext() const
	{
		for (TObjectIterator<UJavascriptContext> It; It; ++It)
		{
			UJavascriptContext* Context = *It;

			if (Context->IsDebugContext())
			{
				return true;
			}
		}

		return false;
	}

	virtual void GetContextIds(TArray<TSharedPtr<FString>>& OutContexts) override
	{
		for (TObjectIterator<UJavascriptContext> It; It; ++It)
		{
			UJavascriptContext* Context = *It;

			if (!Context->IsTemplate(RF_ClassDefaultObject))
			{
				OutContexts.Add(Context->ContextId);
			}
		}
	}

	virtual void SetFlagsFromString(const FString& V8Flags) override
	{
		V8::SetFlagsFromString(TCHAR_TO_ANSI(*V8Flags), strlen(TCHAR_TO_ANSI(*V8Flags)));
	}

	virtual void SetIdleTaskBudget(float BudgetInSeconds) override
	{
		GV8IdleTaskBudget = BudgetInSeconds;
	}

	virtual void* GetV8Platform() override
	{
		return platform_.platform();
	}

	void OnPreGarbageCollection()
	{
		for (TObjectIterator<UJavascriptContext> It; It; ++It)
		{
			UJavascriptContext* Context = *It;

			//Only clear garbage collection on game thread contexts
			if (IsInGameThread() && Context->Thread == EJavascriptAsyncOption::TaskGraphMainThread)
			{
				Context->RequestV8GarbageCollection();
			}
		}
	}
};

IMPLEMENT_MODULE(FV8Module, V8)

PRAGMA_ENABLE_SHADOW_VARIABLE_WARNINGS
