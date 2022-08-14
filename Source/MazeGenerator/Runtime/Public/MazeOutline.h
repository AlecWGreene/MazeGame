// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "MazeGeneratorTypes.h"
#include "MazeOutlinePreviewSettings.h"

#include "MazeOutline.generated.h"

/**
 * This object represents a template for a specific maze layout, which a maze generator can then use
 * to generate different variants or instances based on a seed value. This asset is edited through the 
 * custom MazeGeneratorEditor.
 */
UCLASS(BlueprintType)
class MAZEGENERATOR_API UMazeOutline : public UObject
{
	GENERATED_BODY()

public:

	/** Number of concentric rings which make up the graph. Equivalent to the number of nodes from the center to the outside of the graph along a spoke. Must be at least 1. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 NumRings{ 1 };

	/** Number of sides each concentric polygon has. Must be at least 3. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 NumSides{ 3 };

	/** When true, mazes generated from this outline will randomly select starting nodes from the array. Otherwise they are selected based on array index. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bRandomStarts{ false };

	/** Number of nodes to use as starting locations. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 NumStarts{ 1 };

	/** Potential starting locations. These are used as the origin of some maze algorithms if available. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FMazeLocation> StartNodes;

	/** When true, mazes generated from this outlien will randomly select ending nodes from the array. Otherwise they are selected based on array index. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bRandomEnds{ false };

	/** Number of nodes to use as maze completion locations. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 NumEnds{ 1 };

	/** Potential ending locations. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FMazeLocation> EndNodes;

	/** Polygonal SubGraphs which will be used to generate the maze piece-wise with different algorithms. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FMazeFragmentOutline> Fragments;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	FMazeOutlinePreviewSettings PreviewSettings;
#endif
};