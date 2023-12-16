// Fill out your copyright notice in the Description page of Project Settings.

#include "Graph/Custom_shape.h"

// Sets default values
ACustom_shape::ACustom_shape()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("node_mesh"));
	staticMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	staticMesh->Mobility = EComponentMobility::Movable;
	plane =
		ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Nav/untitled.untitled'")).Object;
	staticMesh->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));

	staticMesh->ComponentTags.AddUnique(TEXT("self"));
	staticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	staticMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	staticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	staticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	RootComponent = staticMesh;
	// CollisionComponent->SetRelativeScale3D(FScale());

	if (plane && staticMesh)
	{
		staticMesh->SetStaticMesh(plane);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("mesh does not exist"), "blank");
	}

	// // Bind the overlap event
}

// Called when the game starts or when spawned
void ACustom_shape::BeginPlay()
{
	Super::BeginPlay();
	// set up a notification for when this component overlaps something

	// Bind the overlap event function
	staticMesh->OnComponentBeginOverlap.AddDynamic(this, &ACustom_shape::OnOverlapBegin); // set up a notification for when this component overlaps something
	staticMesh->OnComponentEndOverlap.AddDynamic(this, &ACustom_shape::OnOverlapEnd);


}

// Called every frame
void ACustom_shape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustom_shape::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	if (OtherComp && OtherComp->ComponentTags.Num()>0)
	{

		UE_LOG(LogTemp, Warning, TEXT("were colliding %s"), *OtherComp->ComponentTags[0].ToString());
	}
	is_coliding = true;
}

void ACustom_shape::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap NOT WORKING BITTCH!!!"));
	if (OtherComp &&  OtherComp->ComponentTags.Num()>0)
	{

		UE_LOG(LogTemp, Warning, TEXT("were not colliding with %s"), *OtherComp->ComponentTags[0].ToString());
	}
	is_coliding = false;
}
