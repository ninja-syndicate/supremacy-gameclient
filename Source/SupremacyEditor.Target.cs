// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SupremacyEditorTarget : TargetRules
{
	public SupremacyEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		// Changes in the plugin may not get detected if adaptive unity build is enabled.
		// This works in Perforce, but not for Git.
		bUseAdaptiveUnityBuild = false;

		ExtraModuleNames.AddRange( new string[] { "Supremacy" } );
    }
}
