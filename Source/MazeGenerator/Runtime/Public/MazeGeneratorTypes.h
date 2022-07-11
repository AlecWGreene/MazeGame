// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "MazeGeneratorTypes.generated.h"

/** 
 * Represents the different maze generation algorithms implemented 
 */
UENUM(BlueprintType)
enum class EMazeStyle : uint8
{
	None,
	Branch,
	Ring,
	Braid
};

/** 
 * Represents a position on the maze graph. 
 */
USTRUCT(BlueprintType)
struct MAZEGENERATOR_API FMazeLocation
{
	GENERATED_BODY()

public:

	/** Default constructor will return an invalid location. Use the other signature instead. */
	FMazeLocation() : Ring(-1), Position(-1) {}

	FMazeLocation(uint32 InRing, uint32 InPosition) : Ring(InRing), Position(InPosition) {}

	/** Index of the concentric ring the location belongs to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Ring{ 0 };

	/** Position is the index of the location within the ring, 0 is always along the positive x-axis "spoke" of the graph. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Position{ 0 };

	/** Invalid static instance to use as bad returns. */
	static FMazeLocation Invalid;
};

/** 
 * A series of connected maze graph nodes forming a straight line.
 * TODO(agreene): Decide on support for "jagged" lines
 */
USTRUCT(BlueprintType)
struct MAZEGENERATOR_API FMazeLineSegment
{
	GENERATED_BODY()

public:

	FMazeLineSegment() {}

	UPROPERTY(BlueprintReadOnly)
	TArray<FMazeLocation> Nodes;

	const FMazeLocation& GetStart() const
	{
		return Nodes.IsEmpty() ? FMazeLocation::Invalid : Nodes[0];
	}

	const FMazeLocation& GetEnd() const
	{
		return Nodes.IsEmpty() ? FMazeLocation::Invalid : Nodes.Last();
	}
};

/**
 * Represents an outline of a maze graph fragment for the generator to use for fragment generation. 
 * Only polygons are supported currently.
 */
USTRUCT(BlueprintType)
struct MAZEGENERATOR_API FMazeFragmentOutline
{
	GENERATED_BODY()

public:

	FMazeFragmentOutline() {}

	/** Style to use when connecting nodes within this fragment. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMazeStyle Style{ EMazeStyle::None };

	/** Segments defining the boundaries of the fragment. */
	TArray<FMazeLineSegment> Boundaries;
};