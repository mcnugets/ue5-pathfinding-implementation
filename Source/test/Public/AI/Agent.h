// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"
#include "Graph/Custom_graph.h"
#include "Graph_Manager.h"
#include "Agent.generated.h"


UCLASS()
class TEST_API AAgent : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAgent();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *agent_body;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent *capsule;

	UPROPERTY()
	ACustom_graph *graph;

	UPROPERTY(EditAnywhere)
	float speed;
	UPROPERTY(EditAnywhere)
	bool is_colliding;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	const float &get_speed() const;
	const bool &get_colliding() const;



	void move();

	ACustom_graph *get_graph() const;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
};
