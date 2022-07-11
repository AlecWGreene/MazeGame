// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "MazeOutlineCache.h"

struct FAssetTypeActions_MazeOutlineCache : FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override
	{
		return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_MazeOutlineCache", "Maze Outline Cache");
	}

	virtual FColor GetTypeColor() const override
	{
		return FColor(255,0,0);
	}

	virtual uint32 GetCategories() override
	{
		return EAssetTypeCategories::Misc;
	}

	virtual UClass* GetSupportedClass() const override
	{
		return UMazeOutlineCache::StaticClass();
	}

	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> ToolkitHost = TSharedPtr<IToolkitHost>()) override;
};