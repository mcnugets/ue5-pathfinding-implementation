// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Custom_shape.generated.h"

UCLASS()
class TEST_API ACustom_shape : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACustom_shape();

	UPROPERTY()
	bool is_coliding = false;

protected:
	UStaticMesh *plane;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *staticMesh;




	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
	void OnOverlapEnd( UPrimitiveComponent *OverlappedComp,  AActor *OtherActor,  UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
