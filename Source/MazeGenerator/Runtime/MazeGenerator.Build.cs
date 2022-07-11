// Copyright 2022 Alec Greene. All Rights Reserverd

using UnrealBuildTool;

public class MazeGenerator : ModuleRules
{
	public MazeGenerator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine"
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject"
			}
			);
	}
}