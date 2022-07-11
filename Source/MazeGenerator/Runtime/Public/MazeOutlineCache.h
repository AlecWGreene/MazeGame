// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "MazeOutlineCache.generated.h"

UCLASS(BlueprintType, Blueprintable)
class MAZEGENERATOR_API UMazeOutlineCache : public UObject
{
	GENERATED_BODY()

public:

	UMazeOutlineCache() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 NumSides{ 0 };

	bool bRandomStartNodes{ false };

	uint32 NumStartNodes{ 1 };

	bool bRandomEndNodes{ false };

	uint32 NumEndNodes{ 1 };
};