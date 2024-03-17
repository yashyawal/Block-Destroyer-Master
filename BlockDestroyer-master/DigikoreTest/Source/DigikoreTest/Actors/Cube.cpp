// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include <Components/StaticMeshComponent.h>
#include <Materials/MaterialInstanceDynamic.h>
// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	//set paramater with Set***ParamaterValue
	int RandomColorIndex = FMath::RandRange(0, Colors.Num() - 1);
	this->ColorIndex = RandomColorIndex;
	DynamicMaterial->SetVectorParameterValue("Color", Colors[RandomColorIndex]);
	CubeMesh->SetMaterial(0, DynamicMaterial);
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

