// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DigikoreTestGameModeBase.generated.h"
class ATileSpawner;
/**
 * 
 */
UCLASS()
class DIGIKORETEST_API ADigikoreTestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATileSpawner* GetTileSpawner() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileSpawner> TileSpawnerAsset;
	virtual void BeginPlay() override;
private:
	ATileSpawner* TileSpawner;
};
