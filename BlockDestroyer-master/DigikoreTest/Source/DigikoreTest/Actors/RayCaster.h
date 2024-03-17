// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RayCaster.generated.h"
class UCameraComponent;
class ACube;
class ATileSpawner;
USTRUCT()
struct FCubeFrequencey
{
	GENERATED_BODY()
public:
	FCubeFrequencey() {};
	TArray<ACube*> CubeArray;

};

UCLASS()
class DIGIKORETEST_API ARayCaster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARayCaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnyWhere)
	TSet<ACube*> TracedCubes;
private:
	UFUNCTION()
	void CastRay();

	UPROPERTY()
	bool bIsRayTraceEnabled;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Destructible;

	ATileSpawner* TileSpawner;
	APlayerController* PlayerController;
};
