// Copyright Alec Greene 2022. All Rights Reserved.

#include "MazeGraph.h"
#include "..\Public\MazeGraph.h"

FMazeGraph::FMazeGraph()
{
}

FMazeGraph::FMazeGraph(uint8 InNumRings, uint8 InNumSides)
{
	Initialize(InNumRings, InNumSides);
}

void FMazeGraph::Initialize(uint8 InNumRings, uint8 InNumSides)
{
	NodeRings.Empty();

	TArray<FMazeGraphNode> RingNodes;
	RingNodes.Reserve(1);
	RingNodes.Add(FMazeGraphNode(0, 0));

	// Origin node doesn't count as a ring towards NumRings
	NumRings = NodeRings.Add(RingNodes);

	if (InNumRings >= 1 && InNumSides >= 3)
	{
		SetNumSides(InNumSides);
		SetNumRings(InNumRings);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[FMazeGraph::Initialize] Could not initialize with %d rings and %d sides"), InNumRings, InNumSides);
	}
}

uint8 FMazeGraph::GetNumRings()
{
	return NumRings;
}

uint8 FMazeGraph::GetNumSides()
{
	return NumSides;
}

void FMazeGraph::SetNumRings(uint8 InNumRings)
{
	if (InNumRings <= 1)
	{
		UE_LOG(LogTemp, Error, TEXT("[FMazeGraph::SetNumRings] Cannot set number of rings to %d, is less than 2."), InNumRings);
		return;
	}

	// Early out if we're not changing anything
	if (InNumRings == NumRings)
	{
		return;
	}

	int32 Direction = (InNumRings - NumRings > 0) ? 1 : -1;
	for (int32 RingIndex = NumRings; RingIndex != InNumRings; RingIndex += Direction)
	{
		if (Direction == 1)
		{
			UE_LOG(LogTemp, Error, TEXT("[FMazeGraph::SetNumRings] Adding ring at index %d"), RingIndex);
			AddRing();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[FMazeGraph::SetNumRings] Removing ring at index %d"), RingIndex);
			RemoveRing();
		}
	}
}

void FMazeGraph::SetNumSides(uint8 InNumSides)
{
	if (InNumSides <= 3)
	{
		UE_LOG(LogTemp, Error, TEXT("[FMazeGraph::SetNumSides] Cannot set number of sides to %d, is less than 3."), InNumSides);
		return;
	}

	// TODO(agreene): Change the graph to add/remove sides
	NumSides = InNumSides;
}

float FMazeGraph::GetNodeWeight(const FMazeLocation& Location) const
{
	const FMazeGraphNode* Node = GetNode(Location);
	return Node ? Node->Weight : 0.0f;
}

TArray<FMazeLocation> FMazeGraph::GetNodeNeighbors(const FMazeLocation& Location) const
{
	const FMazeGraphNode* Node = GetNode(Location);
	return Node ? Node->Neighbors : TArray<FMazeLocation>();
}

TArray<FMazeLocation> FMazeGraph::GetNodeConnections(const FMazeLocation& Location) const
{
	const FMazeGraphNode* Node = GetNode(Location);
	return Node ? Node->Connections : TArray<FMazeLocation>();
}

bool FMazeGraph::AreNodesNeighbors(const FMazeLocation& LocationA, const FMazeLocation& LocationB) const
{
	const FMazeGraphNode* NodeA = GetNode(LocationA);
	const FMazeGraphNode* NodeB = GetNode(LocationB);

	// We only get NodeB to verify the location is valid, the relationship should be symmetrical
	if (NodeA && NodeB)
	{
		return NodeA->Neighbors.Contains(LocationB);
	}

	UE_LOG(LogTemp, Warning, TEXT("[FMazeGraph::AreNodesNeighbors] A node could not be found: %s %s"), *LocationA.ToString(), *LocationB.ToString());
	return false;
}

bool FMazeGraph::AreNodesConnected(const FMazeLocation& LocationA, const FMazeLocation& LocationB) const
{
	const FMazeGraphNode* NodeA = GetNode(LocationA);
	const FMazeGraphNode* NodeB = GetNode(LocationB);

	// We only get NodeB to verify the location is valid, the relationship should be symmetrical
	if (NodeA && NodeB)
	{
		return NodeA->Connections.Contains(LocationB);
	}

	UE_LOG(LogTemp, Warning, TEXT("[FMazeGraph::AreNodesConnected] A node could not be found: %s %s"), *LocationA.ToString(), *LocationB.ToString());
	return false;
}

bool FMazeGraph::ConnectNodes(const FMazeLocation& LocationA, const FMazeLocation& LocationB)
{
	FMazeGraphNode* NodeA = GetNode(LocationA);
	FMazeGraphNode* NodeB = GetNode(LocationB);

	if (NodeA && NodeB)
	{
		if (NodeA->Neighbors.Contains(LocationB))
		{
			NodeA->Connections.AddUnique(LocationB);
			NodeB->Connections.AddUnique(LocationA);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[FMazeGraph::ConnectNodes] Cannot connect non-neighboring nodes: %s %s"), *LocationA.ToString(), *LocationB.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[FMazeGraph::ConnectNodes] A node could not be found: %s %s"), *LocationA.ToString(), *LocationB.ToString());
	}

	return false;
}

bool FMazeGraph::DisconnectNodes(const FMazeLocation& LocationA, const FMazeLocation& LocationB)
{
	FMazeGraphNode* NodeA = GetNode(LocationA);
	FMazeGraphNode* NodeB = GetNode(LocationB);

	if (NodeA && NodeB)
	{
		if (NodeA->Neighbors.Contains(LocationB))
		{
			if (NodeA->Connections.Contains(LocationB))
			{
				NodeA->Connections.Remove(LocationB);
				NodeB->Connections.Remove(LocationA);
				return true;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[FMazeGraph::DisconnectNodes] Cannot disconnect non-connected nodes: %s %s"), *LocationA.ToString(), *LocationB.ToString());
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[FMazeGraph::DisconnectNodes] Cannot disconnect non-neighboring nodes: %s %s"), *LocationA.ToString(), *LocationB.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[FMazeGraph::DisconnectNodes] A node could not be found: %s %s"), *LocationA.ToString(), *LocationB.ToString());
	}

	return false;
}

FMazeGraphNode* FMazeGraph::GetNode(const FMazeLocation& Location)
{
	if (NodeRings.IsValidIndex(Location.Ring))
	{
		if (NodeRings[Location.Ring].IsValidIndex(Location.Position))
		{
			return &NodeRings[Location.Ring][Location.Position];
		}
	}

	return nullptr;
}

const FMazeGraphNode* FMazeGraph::GetNode(const FMazeLocation& Location) const
{
	if (NodeRings.IsValidIndex(Location.Ring))
	{
		if (NodeRings[Location.Ring].IsValidIndex(Location.Position))
		{
			return &NodeRings[Location.Ring][Location.Position];
		}
	}

	return nullptr;
}

bool FMazeGraph::SetNodesNeighbors(const FMazeLocation& LocationA, const FMazeLocation& LocationB)
{
	FMazeGraphNode* NodeA = GetNode(LocationA);
	FMazeGraphNode* NodeB = GetNode(LocationB);

	if (NodeA && NodeB)
	{
		NodeA->Neighbors.AddUnique(LocationB);
		NodeB->Neighbors.AddUnique(LocationA);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[FMazeGraph::SetNodesNeighbors] A node could not be found: %s %s"), *LocationA.ToString(), *LocationB.ToString());
	}

	return false;
}

void FMazeGraph::AddRing()
{
	TArray<FMazeGraphNode> NewRing;
	
	int32 RingIndex = NumRings + 1;
	int32 RingSize = NumSides * RingIndex;
	
	NewRing.Reserve(RingSize);
	NumRings = NodeRings.Add(NewRing);
	
	// Once we have the ring initiailized and added, we insert our new nodes directly to the graph
	TArray<FMazeGraphNode>& RingNodes = NodeRings[RingIndex];
	for (int32 PositionIndex = 0; PositionIndex < RingSize; ++PositionIndex)
	{
		// Location of the node being added
		FMazeLocation NewLocation = FMazeLocation(RingIndex, PositionIndex);
		RingNodes.Add(FMazeGraphNode(NewLocation));
	
		// Set neighbor of node before it in current ring
		if (PositionIndex != 0)
		{
			SetNodesNeighbors(NewLocation, FMazeLocation(RingIndex, PositionIndex - 1));
		}

		// Set first and last nodes of the ring as neighbors
		if (PositionIndex == RingSize - 1)
		{
			SetNodesNeighbors(NewLocation, FMazeLocation(RingIndex, 0));
		}

		// Set neighbors from previous ring
		if (RingIndex == 1)
		{
			SetNodesNeighbors(NewLocation, FMazeLocation(0, 0));
		}
		else
		{
			int32 NewSideNumber = NewLocation.GetSideNumber();
			int32 NewSidePosition = NewLocation.GetSidePosition();

			// Handle corner nodes
			if (NewSidePosition == 0)
			{
				SetNodesNeighbors(
					NewLocation,
					FMazeLocation(
						RingIndex - 1,
						NewSideNumber * (RingIndex - 1)
					)
				);
			}
			else
			{
				// Handle case of a node which neighbors a previous corner node
				if (NewSidePosition == RingIndex - 1)
				{
					int32 NextSideNumber = (NewSideNumber == NumSides - 1) ? 0 : (NewSideNumber + 1);
					SetNodesNeighbors(
						NewLocation,
						FMazeLocation(
							RingIndex - 1,
							NextSideNumber * (RingIndex - 1)
						)
					);
				}
				else
				{
					SetNodesNeighbors(
						NewLocation,
						FMazeLocation(
							RingIndex - 1,
							NewSideNumber * (RingIndex - 1) + NewSidePosition
						)
					);
				}


				SetNodesNeighbors(
					NewLocation,
					FMazeLocation(
						RingIndex - 1,
						NewSideNumber * (RingIndex - 1) + NewSidePosition - 1
					)
				);
			}
		}
	} // for (PositionIndex)
}

void FMazeGraph::RemoveRing()
{
	int32 RingIndex = NumRings;
	int32 PrevRingIndex = RingIndex - 1;
	int32 PrevRingSize = NumSides * PrevRingIndex;
	for (int32 PositionIndex = 0; PositionIndex < PrevRingSize; ++PositionIndex)
	{
		FMazeGraphNode& Node = NodeRings[PrevRingIndex][PositionIndex];
		for (const FMazeLocation& Location : Node.Neighbors)
		{
			// Remove neighbors to the ring we are going to remove
			if (Location.Ring == RingIndex)
			{
				Node.Neighbors.Remove(Location);
			}
		}
	}

	NodeRings.RemoveAt(RingIndex);
	NumRings = PrevRingIndex;
}
