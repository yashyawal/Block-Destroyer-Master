// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"
class UStaticMeshComponent;
class UMaterial;
class UMaterialInstanceDynamic;
UCLASS()
class DIGIKORETEST_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* Material;

	UPROPERTY(VisibleDefaultsOnly)
	UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY(EditDefaultsOnly)
	TArray<FColor> Colors;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int32 Indexi;
	int32 Indexj;
	int32 ColorIndex;
	
};
