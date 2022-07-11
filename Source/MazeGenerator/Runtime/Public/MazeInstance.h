// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "MazeOutline.h"
#include "MazeGraph.h"

#include "MazeInstance.generated.h"

/**
 * WIP
 * Represents a maze generated from an outline. Holds some the layout and a ref to the outline
 * used to generate it. Also includes any data needed to represent runtime changes to the maze.
 */
UCLASS()
class MAZEGENERATOR_API UMazeInstance : public UObject
{
	GENERATED_BODY()

public:

	TSoftObjectPtr<UMazeOutline> Outline;

	/** 
	 * Original maze graph generated using the outline. We cache it off so that we leave room for 
	 *making changes at runtime while still being able to revert.
	 */
	FMazeGraph BaseGraph;
};