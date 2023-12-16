// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Custom_shape.h"
#include "GameFramework/Actor.h"
#include "Custom_graph.generated.h"


UCLASS()
class TEST_API ACustom_graph : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACustom_graph();

	typedef FActorSpawnParameters fasp;
	
	// graph related operations
	UFUNCTION()
	void generate_graph();

	inline const TArray<FVector> get_neighbours(ACustom_shape *current);

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent *the_root;

	UPROPERTY(EditAnywhere)
	UWorld *world;

	UPROPERTY(EditAnywhere)
	ACustom_shape *customshape;

	TMap<FVector, TArray<FVector>>  cells;

	UPROPERTY(EditAnywhere, Category = "Node Spacing")
	float scale;

	UPROPERTY()
	bool do_once;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    const TMap<FVector, TArray<FVector>> &get_cells() const;
	fasp spawn_params(FName name, AActor *owner);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
