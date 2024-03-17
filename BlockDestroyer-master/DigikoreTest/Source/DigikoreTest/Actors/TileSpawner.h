// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileSpawner.generated.h"
class ACube;
USTRUCT()
struct FSlot
{
	GENERATED_BODY()
public:
	FSlot() {};
	FSlot(const FVector& PPosition, ACube* PCube, int32 PIndexi, int32 PIndexj)
	{
		Position = PPosition;
		Cube = PCube;
		Indexi = PIndexi;
		Indexj = PIndexj;
	}

	FVector Position;
	ACube* Cube;
	int32 Indexi;
	int32 Indexj;

};


UCLASS()
class DIGIKORETEST_API ATileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileSpawner();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACube> CubeAsset;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	inline int32 GetMaxHeight()
	{
		return MAX_HEIGHT;
	}
	inline TArray<TArray<FSlot>>& GetSlotMap()
	{
		return SlotMap;
	}

private:
	TArray<TArray<FSlot>> SlotMap;
	const int MAX_HEIGHT = 8;
	const int MAX_WIDTH = 8;
};
