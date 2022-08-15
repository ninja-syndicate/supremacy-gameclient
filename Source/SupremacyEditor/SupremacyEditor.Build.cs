using UnrealBuildTool;

public class SupremacyEditor : ModuleRules
{
	public SupremacyEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicIncludePaths.AddRange(new string[]{"SupremacyEditor/Public"});
		PrivateIncludePaths.AddRange(new string[]{"SupremacyEditor/Private"});
		
		PublicDependencyModuleNames.AddRange(new string[]{ "Supremacy"});
		
		PrivateDependencyModuleNames.AddRange(new []{"Core", "CoreUObject", "Engine"});
		
		PrivateIncludePathModuleNames.AddRange(new string[]{});

		DynamicallyLoadedModuleNames.AddRange(new string[]{});
	}
}