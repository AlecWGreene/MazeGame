// Copyright 2022 Alec Greene. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "MazeOutlinePreviewSettings.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FMazeOutlinePreviewSettings
{
	GENERATED_BODY();

	FMazeOutlinePreviewSettings() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Show Nodes"))
	bool bShowNodes{ true };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Show Neighbor Edges"))
	bool bShowNeighborEdges{ true };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Show Connection Edges"))
	bool bShowConnectionEdges{ true };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Preview Seed"))
	FString RandomSeed{ TEXT("AlecGreene") };

};