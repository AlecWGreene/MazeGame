// Copyright Alec Greene 2022. All Rights Reserved.

#include "MazeGeneratorTypes.h"
#include "..\Public\MazeGeneratorTypes.h"

FMazeLocation FMazeLocation::Invalid = FMazeLocation();

int32 FMazeLocation::GetSideNumber() const
{
	return FMath::Floor(Position / Ring);
}

int32 FMazeLocation::GetSidePosition() const
{
	return Position % Ring;
}

FString FMazeLocation::ToString() const
{
	return FString::Printf(TEXT("MazeLoc(%f,%f)"), Ring, Position);
}
