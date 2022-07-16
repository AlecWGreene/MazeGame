// Copyright Alec Greene 2022. All Rights Reserved.

using UnrealBuildTool;

public class MazeGeneratorEditor : ModuleRules
{
	public MazeGeneratorEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealEd",
				"EditorFramework",
				"AdvancedPreviewScene",
				"EditorScriptingUtilities",
				"MazeGenerator",
				"Engine"
			}	
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"UnrealEd",
				"InputCore",
				"LevelEditor",
				"CoreUObject",
				"UMG",
				"UMGEditor",
				"EditorStyle",
				"Slate",
				"SlateCore",
				"AssetRegistry",
				"AssetTools",
				"RenderCore",
				"PropertyEditor"
			}
			);

	}
}