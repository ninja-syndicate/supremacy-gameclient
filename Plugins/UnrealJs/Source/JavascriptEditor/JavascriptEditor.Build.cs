﻿using UnrealBuildTool;

public class JavascriptEditor : ModuleRules
{
    public static bool IsVREditorNeeded()
    {
        string[] VersionHeader = Utils.ReadAllText("../Source/Runtime/Launch/Resources/Version.h").Replace("\r\n", "\n").Replace("\t", " ").Split('\n');
        string EngineVersionMajor = "4";
        string EngineVersionMinor = "0";
        foreach (string Line in VersionHeader)
        {
            if (Line.StartsWith("#define ENGINE_MAJOR_VERSION "))
            {
                EngineVersionMajor = Line.Split(' ')[2];
            }
            else if (Line.StartsWith("#define ENGINE_MINOR_VERSION "))
            {
                EngineVersionMinor = Line.Split(' ')[2];
            }
        }
        return System.Int32.Parse(EngineVersionMajor) == 4 && System.Int32.Parse(EngineVersionMinor) >= 14;
    }

    public JavascriptEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(
                new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"Slate",
                    "Landscape",
                    "JavascriptUMG",
                    "RawMesh",
                    "NavigationSystem",
                    "WebBrowser",
                    "AppFramework",
                    "KismetWidgets",
                    "EditorStyle",
                    "UnrealEd",
                    "JavascriptUMG",
                    "DetailCustomizations"
                }
            );	// @todo Mac: for some reason CoreUObject and Engine are needed to link in debug on Mac

        if (Target.bBuildEditor == true)
        {
            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "AssetRegistry",
                }
            );

            if (IsVREditorNeeded())
            {
                PrivateDependencyModuleNames.AddRange(new string []{ "LevelEditor", "ViewportInteraction", "VREditor" });
            }

            PrivateDependencyModuleNames.AddRange(
                new string[]
				    {
					    // ... add private dependencies that you statically link with here ...
					    "Core",
					    "CoreUObject",
					    "Engine",
					    "AssetTools",
					    "ClassViewer",
                        "InputCore",
                        "CurveTableEditor",
                        "PropertyEditor",
                        "AdvancedPreviewScene",
                        "Slate",
					    "SlateCore",
                        "EditorStyle",
					    "MainFrame",
                        "EditorFramework",
                        "UnrealEd",
                        "WorkspaceMenuStructure",
                        "V8",
                        "UMG",
                        "Foliage",
                        "LandscapeEditor",
                        "KismetWidgets",
                        "Kismet",
                        "AnimationBlueprintEditor",
                        "AnimationEditor",
                        "ImageWrapper",
                        "RenderCore",
                        "RHI",
				        "DesktopPlatform",
                        "ToolMenus",
                        "SkeletalMeshEditor",
                        "StaticMeshEditor"
                    }
            );
        }

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }
	}
}
