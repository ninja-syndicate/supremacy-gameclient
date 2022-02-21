using UnrealBuildTool;

public class OBJPoolDeveloper : ModuleRules {
	public OBJPoolDeveloper(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;
		//
		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"Slate",
				"Engine",
				"OBJPool",
				"SlateCore",
				"CoreUObject"
			}///
		);//
		//
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Projects",
				"KismetCompiler"
			}///
		);///
		//
		if (Target.bBuildEditor==true) {
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"UnrealEd",
					"LevelEditor",
					"PropertyEditor",
					"BlueprintGraph"
				}///
			);///
		}///
	}///
}