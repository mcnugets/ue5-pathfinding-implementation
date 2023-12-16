// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Pathfinding.h"

// Sets default values
APathfinding::APathfinding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
APathfinding::APathfinding(Anode_g &start, Anode_g &end) : start(&start), end(&end)
{
}
const TMap<FVector, FVector> &APathfinding::get_path() const
{
	return m_path;
}
void APathfinding::dijkstras()
{
	graph = AGraph_Manager::graph_instance(GetWorld());
	// create custom struct for FVector that would support '<' operator
	pqueue.push(start);
	m_path.Add(start->get_pos(), FVector::ZeroVector);
	TMap<FVector, TArray<FVector>> graph_cell = graph->get_cells();

	for (auto it = graph_cell.begin(); it != graph_cell.end(); ++it)
	{
		m_path.Add(it->Key, FVector::ZeroVector);
		visited_m.Add(it->Key,0);
		for (int n = 0; n < it->Value.Num(); ++n)
		{
			m_path.Add(it->Value[n], FVector::ZeroVector);
			visited_m.Add(it->Value[n]);
		}
	}


	while (!pqueue.empty())
	{
		Anode_g *current = pqueue.top();
		pqueue.pop();
		FVector current_pos = current->get_pos();

		visited_m[current_pos] = 1;
		
		for (FVector V : graph_cell[current_pos])
		{
			Anode_g v_node = Anode_g(V, current->get_cost() + 1.0f, false);
			pqueue.push(&v_node);

		}
	}
}
// Called when the game starts or when spawned
void APathfinding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APathfinding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
