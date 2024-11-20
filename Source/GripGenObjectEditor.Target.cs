// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GripGenObjectEditorTarget : TargetRules
{
	public GripGenObjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "GripGenObject", "HeadMountedDisplay", "OculusXRInput", "OculusXRHMD" } );
	}
}
