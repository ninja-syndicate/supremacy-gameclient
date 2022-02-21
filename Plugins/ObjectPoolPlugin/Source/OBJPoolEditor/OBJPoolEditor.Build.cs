using UnrealBuildTool;

public class OBJPoolEditor : ModuleRules {
    public OBJPoolEditor(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "Public/OBJPoolEditor.h";
		bEnforceIWYU = true;
		//
        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "Engine",
                "OBJPool",
                "CoreUObject",
                "OBJPoolDeveloper"
            }///
        );//
        //
        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Slate",
                "Projects",
                "UnrealEd",
                "SlateCore",
                "AssetTools",
                "EditorStyle",
                "LevelEditor"
            }///
        );//
    }///
}