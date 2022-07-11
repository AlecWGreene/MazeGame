// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "MazeGeneratorTypes.h"

#include "MazeGraph.generated.h"

/** 
 * One of the nodes in a maze graph. Stores a weight as well as connection data. 
 */
USTRUCT(BlueprintType)
struct FMazeGraphNode
{

	GENERATED_BODY()

public:

	FMazeGraphNode() {}
	FMazeGraphNode(const FMazeLocation& InLocation) : Location(InLocation) {}
	FMazeGraphNode(int32 Ring, int32 Position) : Location(FMazeLocation(Ring, Position)) {}

	/** Float value used for maze algorithms. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Weight{ 0.f };

	/** Position of the node in the maze graph. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FMazeLocation Location{ FMazeLocation::Invalid };

	/** All valid possible connections. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FMazeLocation> Neighbors;

	/** Connections formed in the maze graph. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FMazeLocation> Connections;
};

/**
 * A graph representing a maze layout. Nodes are connected to represent hallways,
 * most of the data manipulation to be done on nodes should be done through the
 * public API on this struct.
 * 
 * Most of the configuration data should be generated using a UMazeOutline object,
 * this struct is meant to hold graph data for an outline isntance.
 */
USTRUCT(BlueprintType)
struct MAZEGENERATOR_API FMazeGraph
{
	GENERATED_BODY()

	//---------- Constructors and Destructors ----------//
public:

	FMazeGraph();
	FMazeGraph(uint8 InNumRings, uint8 InNumSides);
	
	//---------- Maze Graph Getters/Setters ----------//
public:

	uint8 GetNumRings();

	uint8 GetNumSides();

protected:

	/** Sets the number of concentric rings which make up the graph. Should be greater than 1. */
	void SetNumRings(uint8 InNumRings);

	/** Sets the number of sides each concentric polygon has. Must be at least 3. */
	void SetNumSides(uint8 InNumSides);

	//---------- Maze Graph Node Methods ----------//
public:

	/** Gets weight of a node, used for maze generation algorithms. */
	float GetNodeWeight(const FMazeLocation& Location) const;

	TArray<FMazeLocation> GetNodeNeighbors(const FMazeLocation& Location) const;

	TArray<FMazeLocation> GetNodeConnections(const FMazeLocation& Location) const;

	bool AreNodesNeighbors(const FMazeLocation& LocationA, const FMazeLocation& LocationB) const;

	bool AreNodesConnected(const FMazeLocation& LocationA, const FMazeLocation& LocationB) const;

	bool ConnectNodes(const FMazeLocation& LocationA, const FMazeLocation& LocationB);

	bool DisconnectNodes(const FMazeLocation& LocationA, const FMazeLocation& LocationB);

protected:

	/** Sets the nodes at locations A and B to either be neighbors or not depending on bNewRelationShip. */
	bool SetNodesNeighbors(const FMazeLocation& LocationA, const FMazeLocation& LocationB, bool bNewRelationShip);

	//---------- Instance Variables ----------//
protected:
	
	uint8 NumRings{ 0 };

	uint8 NumSides{ 0 };

	/** 2-D jagged array of graph nodes representing concentric n-gons. */
	TArray<TArray<FMazeGraphNode>> NodeRings;
};