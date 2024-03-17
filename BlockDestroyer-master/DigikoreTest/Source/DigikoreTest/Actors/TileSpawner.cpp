// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSpawner.h"
#include "DigikoreTest/Actors/Cube.h"
// Sets default values
ATileSpawner::ATileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATileSpawner::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		TArray<FSlot> Slots;
		for (int j = 0; j < MAX_WIDTH; j++)
		{
			FVector Position = FVector(GetActorLocation().X, this->GetActorLocation().Y+ (j*100), GetActorLocation().Z+ (i*100));
			ACube* Cube = GetWorld()->SpawnActor<ACube>(CubeAsset,Position,FRotator::ZeroRotator);
			Cube->SetActorLocation(Position);
			Cube->Indexi = i;
			Cube->Indexj = j;
			FSlot Slot(Position,Cube,i,j);
			Slots.Add(Slot);
		}
		SlotMap.Add(Slots);
	}
}

// Called every frame
void ATileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

