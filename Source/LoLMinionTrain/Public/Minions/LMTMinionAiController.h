// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LMTMinionAiController.generated.h"

/**
 * 
 */
UCLASS()
class LOLMINIONTRAIN_API ALMTMinionAiController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class ALMTMinionBase* ControlledMinion;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> OverlappedTargets;

	UPROPERTY(VisibleAnywhere)
	class ALMTBaseCharacter* CurrentTarget;

	UPROPERTY(VisibleAnywhere)
	bool bMoving;
	
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void MoveToLaneEnd();
	
	UFUNCTION()
	void CheckOverlappingTargets();

	UFUNCTION()
	FVector GetNearestLocationOnLane();

	
	
	
};
