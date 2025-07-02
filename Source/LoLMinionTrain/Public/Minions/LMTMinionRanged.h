// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minions/LMTMinionBase.h"
#include "LMTMinionRanged.generated.h"

/**
 * 
 */
UCLASS()
class LOLMINIONTRAIN_API ALMTMinionRanged : public ALMTMinionBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TSubclassOf<class ALMTProjectileBase> ProjectileClass;

public:
	UFUNCTION(BlueprintCallable)
	void FireProjectile();
};
