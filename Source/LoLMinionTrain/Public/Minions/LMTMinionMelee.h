// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minions/LMTMinionBase.h"
#include "LMTMinionMelee.generated.h"

/**
 * 
 */
UCLASS()
class LOLMINIONTRAIN_API ALMTMinionMelee : public ALMTMinionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ApplyMeleeDamageToTarget();
	
};
