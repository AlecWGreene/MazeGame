// Copyright Alec Greene 2022. All Rights Reserved.

#include "MazeGeneratorEditor.h"

#include "AssetToolsModule.h"
#include "IAssetTypeActions.h"
#include "IAssetTools.h"

#include "AssetTypeActions_MazeOutline.h"

IMPLEMENT_MODULE(FMazeGeneratorEditorModule, MazeGeneratorEditor)

void FMazeGeneratorEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_MazeOutline()));
}

void FMazeGeneratorEditorModule::ShutdownModule()
{
}