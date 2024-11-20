// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GripGenObjectTarget : TargetRules
{
	public GripGenObjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "GripGenObject", "HeadMountedDisplay", "OculusXRInput", "OculusXRHMD" } );
    }
}
