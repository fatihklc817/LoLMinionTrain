// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LMT_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LOLMINIONTRAIN_API ALMT_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALMTMinionBase> RedMeleeMinionClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALMTMinionBase> RedRangedMinionClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALMTMinionBase> BlueMeleeMinionClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALMTMinionBase> BlueRangedMinionClass;
	
	
	int32 MeleeMinionSpawnCount= 3;
	int32 BlueMeleeMinionSpawnCount= 3;
	int32 RedMeleeMinionSpawnCount= 3;
	
	int32 RangedMinionSpawnCount= 3;
	int32 BlueRangedMinionSpawnCount= 3;
	int32 RedRangedMinionSpawnCount= 3;

	FTimerHandle MinionSpawnHandle;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SpawnMinionWaves();

	UFUNCTION()
	void SpawnNextMinion();
};
