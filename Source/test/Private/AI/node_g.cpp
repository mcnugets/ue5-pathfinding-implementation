// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/node_g.h"

Anode_g::Anode_g()
{
	PrimaryActorTick.bCanEverTick = true;
}
// Sets default values
Anode_g::Anode_g(FVector pos, float cost, bool is_visited) : pos(pos), cost(cost), is_visited(is_visited)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

void Anode_g::set_visited(bool flag)
{
	is_visited = flag;
}
const FVector &Anode_g::get_pos() const
{
	return pos;
}
const float &Anode_g::get_cost() const
{
	return cost;
}
const bool &Anode_g::get_is_visited() const
{
	return is_visited;
}
