// Fill out your copyright notice in the Description page of Project Settings.

// THIS IS A BASE SO DO SAY SKELETON CLASS FOR THE ENEMY NPS
// THIS MEANS THIS WILL WORK AS A PARENT CLASS
// AND LATER MULTIPLE VARIATTION OF ENEMIES WILL BE INHERTED FROM THE CLASS

#include "AI/Agent.h"
// Sets default values
AAgent::AAgent() : agent_body(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("agent_body"))),
				   capsule(CreateDefaultSubobject<UCapsuleComponent>(TEXT("agent_capsule"))),
				   speed(0.0f),
				   is_colliding(false)

{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = capsule;
	agent_body->SetupAttachment(capsule);
	ConstructorHelpers::FObjectFinder<UStaticMesh> cube_mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (cube_mesh.Succeeded())
		agent_body->SetStaticMesh(cube_mesh.Object);
	agent_body->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.5f));
	agent_body->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	capsule->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

const float &AAgent::get_speed() const
{
	return speed;
}
const bool &AAgent::get_colliding() const
{
	return is_colliding;
}
ACustom_graph *AAgent::get_graph() const
{
	return graph;
}

// void ACustom_graph::move()
// {

// }

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	capsule->OnComponentBeginOverlap.AddDynamic(this, &AAgent::OnOverlapBegin);
	capsule->OnComponentEndOverlap.AddDynamic(this, &AAgent::OnOverlapEnd);

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("We are colliding with the cell %s " + *grid->get_cells()[0]->GetName()));
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AAgent::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

	FString MaterialPath = TEXT("/Game/materials/purple.purple");

	// Load the material using StaticLoadObject
	UMaterial *LoadedMaterial = LoadObject<UMaterial>(nullptr, *MaterialPath);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("We are colliding with the cell %s"));
	UE_LOG(LogTemp, Warning, TEXT("======================================================================"));
	is_colliding = true;
	if (OtherActor && OtherActor != GetOwner())
	{
		// Print debug message
		UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());
		OtherComp->SetMaterial(0, LoadedMaterial);
		// Draw debug sphere at the overlap location
		DrawDebugSphere(GetWorld(), SweepResult.ImpactPoint, 30.0f, 12, FColor::Green, false, 2.0f);
	}
}
void AAgent::OnOverlapEnd(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	is_colliding = false;
}
