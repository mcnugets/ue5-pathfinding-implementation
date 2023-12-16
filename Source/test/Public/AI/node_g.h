// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "node_g.generated.h"

UCLASS()
class TEST_API Anode_g : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Anode_g();
	Anode_g(FVector pos, float cost, bool is_visited);


protected:
	FVector pos;
	float cost;
	bool is_visited;

	

public:
	void set_visited(bool flag);
	const FVector &get_pos() const;
	const float &get_cost() const;
	const bool &get_is_visited() const;

	
};
