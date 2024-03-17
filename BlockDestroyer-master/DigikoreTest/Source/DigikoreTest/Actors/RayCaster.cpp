// Fill out your copyright notice in the Description page of Project Settings.


#include "RayCaster.h"
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Camera/PlayerCameraManager.h>
#include <DigikoreTest/Actors/Cube.h>
#include <DigikoreTest/DigikoreTestGameModeBase.h>
#include <Kismet/GameplayStatics.h>
#include <DigikoreTest/Actors/TileSpawner.h>
// Sets default values
ARayCaster::ARayCaster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("RayCaster");
}

// Called when the game starts or when spawned
void ARayCaster::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeGameAndUI InputMode;
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(InputMode);
	}
	const ADigikoreTestGameModeBase* Mode = Cast<ADigikoreTestGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (Mode)
	{
		TileSpawner = Mode->GetTileSpawner();
	}
}

// Called every frame
void ARayCaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsRayTraceEnabled)
	{
		FHitResult Hit;
		if (PlayerController)
		{
			double X,Y;
			PlayerController->GetMousePosition(X, Y);
			FVector WorldPosition , WorldDirection;
			PlayerController->DeprojectScreenPositionToWorld(X, Y, WorldPosition, WorldDirection);

			FVector TraceStart = WorldPosition + FVector(100.0f,0,0);
			FVector TraceEnd = WorldPosition + (WorldDirection) * 10000.0f;

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);

			GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
			UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

			if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
			{
				UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
				if (ACube* Cube = Cast<ACube>(Hit.GetActor()))
				{
					TracedCubes.Add(Cube);
				}
			}
			else 
			{
				UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
			}
		}
	}
}

// Called to bind functionality to input
void ARayCaster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Click", IE_Pressed, this, &ARayCaster::CastRay);
}

void ARayCaster::CastRay()
{
	bIsRayTraceEnabled =!bIsRayTraceEnabled;
	if (!bIsRayTraceEnabled)
	{
		int32 Counter = 0;
		TMap<int32 , FCubeFrequencey> FrequencyMap;
		TArray<TPair<int32,int32>> ColumnIndex;

		//clean traced cube set for non adjecent elements 
		TArray<ACube*> TempArray;
		TArray<ACube*> ConvCubeArray = TracedCubes.Array();
		TArray<ACube*> StrippedArray;
		

		ACube* PreviousElement = ConvCubeArray[0];
		TempArray.Add(ConvCubeArray[0]);
		for (int i=1;i<ConvCubeArray.Num();i++)
		{
			if (ConvCubeArray[i]->ColorIndex == PreviousElement->ColorIndex)
			{
				TempArray.Add(ConvCubeArray[i]);
			}
			else
			{
				if (TempArray.Num() >= 3)
				{
					StrippedArray.Append(TempArray);
				}
				TempArray.Empty();
				TempArray.Add(ConvCubeArray[i]);
				PreviousElement = ConvCubeArray[i];
			}

		}
		if (TempArray.Num() >= 3)
		{
			StrippedArray.Append(TempArray);
		}

		TempArray.Empty();

		for (auto &Cube : StrippedArray)
		{
			TPair<int32, int32> Index;
			Index.Key = Cube->Indexi;
			Index.Value = Cube->Indexj;
			ColumnIndex.Add(Index);
			Cube->Destroy();	
		}
		StrippedArray.Empty();
		TracedCubes.Empty();
		for (const TPair<int32, int32>& P : ColumnIndex)
		{
			if (P.Key != TileSpawner->GetMaxHeight()-1)
			{
				int j = P.Value;
				int i = P.Key;
				for (; i < TileSpawner->GetMaxHeight()-1; i++)
				{
					
					if (TileSpawner->GetSlotMap()[i + 1][j].Cube != nullptr)
					{
						ACube* UpperCube = TileSpawner->GetSlotMap()[i + 1][j].Cube;
						UpperCube->SetActorLocation(TileSpawner->GetSlotMap()[i][j].Position);
						UpperCube->Indexi = i;
						UpperCube->Indexj = j;
						TileSpawner->GetSlotMap()[i + 1][j].Cube = nullptr;
						TileSpawner->GetSlotMap()[i][j].Cube = UpperCube;
					
					}
					else
					{
						break;
					}
				}
				// Create a random colored cube for the last height index and initialize the last height index of slot to the newly created cube  
			}
			else
			{
				// Create a random colored cube for the last height index and initialize the last height index of slot to the newly created cube  

			}
		}
	}
}

