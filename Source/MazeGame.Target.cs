// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MazeGameTarget : TargetRules
{
	public MazeGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MazeGame");
		ExtraModuleNames.Add("MazeGenerator");
		ExtraModuleNames.Add("MazeGeneratorEditor");
	}
}
