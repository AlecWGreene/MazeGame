// Copyright Alec Greene 2022. All Rights Reserved.

#include "AssetTypeActions_MazeOutlineCache.h"

#include "MazeOutlineCache.h"
#include "AssetEditor/MazeOutlineAssetEditor.h"

void FAssetTypeActions_MazeOutlineCache::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> ToolkitHost)
{
	for (UObject* Object : InObjects)
	{
		if (UMazeOutlineCache* OutlineCache = Cast<UMazeOutlineCache>(Object))
		{
			TSharedRef<FMazeOutlineAssetEditor> Editor(new FMazeOutlineAssetEditor());
			Editor->SetupEditor(EToolkitMode::Standalone, ToolkitHost, OutlineCache);
		}
	}
}