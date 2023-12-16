// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Graph/Custom_graph.h"
#include "Kismet/GameplayStatics.h"
#include "Graph_Manager.generated.h"

UCLASS()
class TEST_API AGraph_Manager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGraph_Manager();

	static  ACustom_graph *graph_instance(UWorld *world);
	void set_graph(UWorld *world);

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
