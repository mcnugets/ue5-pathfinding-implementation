// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Graph_Manager.h"

// Sets default values
AGraph_Manager::AGraph_Manager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

inline ACustom_graph *AGraph_Manager::graph_instance(UWorld* world)
{
	return world ? Cast<ACustom_graph>(UGameplayStatics::GetActorOfClass(world, ACustom_graph::StaticClass()))
	: nullptr;
	
}

// Called when the game starts or when spawned
void AGraph_Manager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGraph_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
