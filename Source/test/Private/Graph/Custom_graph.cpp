// Fill out your copyright notice in the Description page of Project Settings.

#include "Graph/Custom_graph.h"

// Sets default values
ACustom_graph::ACustom_graph() : 
the_root(CreateDefaultSubobject<USceneComponent>("root compo")),
world(nullptr),
scale(0.0f),
do_once(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	the_root->Mobility = EComponentMobility::Movable;
	RootComponent = the_root;
	
}

const TMap<FVector, TArray<FVector>> &ACustom_graph::get_cells() const
{
	return cells;
}
FActorSpawnParameters ACustom_graph::spawn_params(FName name, AActor *owner)
{
	fasp params;
	params.Name = MakeUniqueObjectName(this, ACustom_shape::StaticClass(), FName(name));
	AActor *this_owner = owner;
	params.Owner = this_owner;
	return params;
}

inline const TArray<FVector> ACustom_graph::get_neighbours(ACustom_shape *current)
{
	TArray<FVector> shapes;
	FVector current_pos = current->GetActorLocation();
	shapes.Add(current_pos + FVector(scale, 0.0f, 0.0f));
	shapes.Add(current_pos + FVector(-scale, 0.0f, 0.0f));
	shapes.Add(current_pos + FVector(0.0f, scale, 0.0f));
	shapes.Add(current_pos + FVector(0.0f, -scale, 0.0f));
	return shapes;
}

void ACustom_graph::generate_graph()
{
	TQueue<FVector> queue;
	TSet<FVector> visited;
	queue.Enqueue(RootComponent->GetRelativeLocation());
	visited.Add(RootComponent->GetRelativeLocation());
	int count = 0;
	if(world)
		while (!queue.IsEmpty())
		{

			FVector current_pos = *queue.Peek();
			queue.Pop();

			ACustom_shape *current = world->SpawnActor<ACustom_shape>(
				ACustom_shape::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				spawn_params("spawned_plane", this));

			current->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

			current->SetActorLocation(current_pos);

			if(!cells.Contains(current->GetActorLocation()))
				cells.Add(current->GetActorLocation(), {});
			if (!current->is_coliding)
			{

				for (FVector N : get_neighbours(current))
				{
					if (!visited.Contains(N)){
						cells[current->GetActorLocation()].Add(N);
						queue.Enqueue(N);
						visited.Add(N);
					}
					
				}
			}
		}
}

// Called when the game starts or when spawned
void ACustom_graph::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
}

// Called every frame
void ACustom_graph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!do_once)
	{
		// spawn_shape(dimensions);
		if (scale == 0.0f)
		{
			UE_LOG(LogTemp, Error, TEXT("Please set scale value"));
		}
		else
		{
			generate_graph();
		}
		do_once = true;
	}
}
