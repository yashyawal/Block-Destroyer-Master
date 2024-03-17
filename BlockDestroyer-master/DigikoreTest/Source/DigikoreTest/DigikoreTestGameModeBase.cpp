// Copyright Epic Games, Inc. All Rights Reserved.


#include "DigikoreTestGameModeBase.h"
#include "DigikoreTest/Actors/TileSpawner.h"
ATileSpawner* ADigikoreTestGameModeBase::GetTileSpawner() const
{
	return TileSpawner;
}

void ADigikoreTestGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	FVector Position = FVector(150.0f, -180.0f, 0.0f);
	TileSpawner = GetWorld()->SpawnActor<ATileSpawner>(TileSpawnerAsset, Position, FRotator::ZeroRotator);
}
