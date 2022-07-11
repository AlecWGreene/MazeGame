// Copyright Alec Greene 2022. All Rights Reserved.

#include "AssetTypeActions_MazeOutline.h"

#include "MazeOutline.h"
#include "AssetEditor/MazeOutlineAssetEditor.h"

void FAssetTypeActions_MazeOutline::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> ToolkitHost)
{
	for (UObject* Object : InObjects)
	{
		if (UMazeOutline* OutlineCache = Cast<UMazeOutline>(Object))
		{
			TSharedRef<FMazeOutlineAssetEditor> Editor(new FMazeOutlineAssetEditor());
			Editor->SetupEditor(EToolkitMode::Standalone, ToolkitHost, OutlineCache);
		}
	}
}