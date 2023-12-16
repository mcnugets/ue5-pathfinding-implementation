// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "node_g.h"
#include "Graph_Manager.h"
#include <queue>
#include "Pathfinding.generated.h"

UCLASS()
class TEST_API APathfinding : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APathfinding();
	APathfinding(Anode_g &start, Anode_g &end);

protected:
	UPROPERTY()
	ACustom_graph *graph;

	std::priority_queue<Anode_g *> pqueue;
	TMap<FVector, bool> visited_m;
	TMap<FVector,FVector> m_path;
	
	Anode_g *start;
	Anode_g *end;

public:
	const TMap<FVector, FVector> &get_path() const;
	void dijkstras();
	void a_star();

	void BeginPlay();

	// Called every frame
	void Tick(float DeltaTime);
};
