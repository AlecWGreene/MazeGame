// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "MazeOutline.h"

struct FAssetTypeActions_MazeOutline : FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override
	{
		return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_MazeOutline", "Maze Outline");
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
		return UMazeOutline::StaticClass();
	}

	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> ToolkitHost = TSharedPtr<IToolkitHost>()) override;
};