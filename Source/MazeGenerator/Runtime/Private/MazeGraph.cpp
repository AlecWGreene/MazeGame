// Copyright Alec Greene 2022. All Rights Reserved.

#include "../Public/MazeGraph.h"

FMazeGraph::FMazeGraph()
{
}

FMazeGraph::FMazeGraph(uint8 InNumRings, uint8 InNumSides)
{
	SetNumRings(InNumRings);
	SetNumSides(InNumSides);
}

uint8 FMazeGraph::GetNumRings()
{
	return NumRings;
}

void FMazeGraph::SetNumRings(uint8 InNumRings)
{
	NumRings = InNumRings;
}

uint8 FMazeGraph::GetNumSides()
{
	return NumSides;
}

void FMazeGraph::SetNumSides(uint8 InNumSides)
{
	if (InNumSides < 3)
	{
		UE_LOG(LogTemp, Error, TEXT("[FMazeGraph::SetNumSides] Cannot set number of sides to %f, is less than 3."), InNumSides);
		return;
	}

	NumSides = InNumSides;
}

float FMazeGraph::GetNodeWeight(const FMazeLocation& Location) const
{
	return 0.0f;
}

TArray<FMazeLocation> FMazeGraph::GetNodeNeighbors(const FMazeLocation& Location) const
{
	return TArray<FMazeLocation>();
}

TArray<FMazeLocation> FMazeGraph::GetNodeConnections(const FMazeLocation& Location) const
{
	return TArray<FMazeLocation>();
}

bool FMazeGraph::AreNodesNeighbors(const FMazeLocation& LocationA, const FMazeLocation& LocationB) const
{
	return false;
}

bool FMazeGraph::AreNodesConnected(const FMazeLocation& LocationA, const FMazeLocation& LocationB) const
{
	return false;
}

bool FMazeGraph::ConnectNodes(const FMazeLocation& LocationA, const FMazeLocation& LocationB)
{
	return false;
}

bool FMazeGraph::DisconnectNodes(const FMazeLocation& LocationA, const FMazeLocation& LocationB)
{
	return false;
}

bool FMazeGraph::SetNodesNeighbors(const FMazeLocation& LocationA, const FMazeLocation& LocationB, bool bNewRelationShip)
{
	return false;
}
