// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/LMTMinionAiController.h"

#include "Components/SphereComponent.h"
#include "Minions/LMTMinionBase.h"

void ALMTMinionAiController::BeginPlay()
{
	Super::BeginPlay();

	ControlledMinion = Cast<ALMTMinionBase>(GetPawn());

	MoveForward();
	

	UE_LOG(LogTemp, Warning, TEXT("ai controller begin "));
}

void ALMTMinionAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FTimerHandle CheckTargetHandle;
	GetWorld()->GetTimerManager().SetTimer(CheckTargetHandle,this,&ALMTMinionAiController::CheckOverlappingTargets,0.5f,true);
	
	
}

void ALMTMinionAiController::MoveForward()
{
	FVector ForwardPoint = ControlledMinion->GetActorLocation() + ControlledMinion->GetActorForwardVector() * 1000;
	MoveToLocation(ForwardPoint);
}

void ALMTMinionAiController::CheckOverlappingTargets()
{
	USphereComponent* AttackRangeSphere = ControlledMinion->GetAttackRangeSphere();
	OverlappedTargets.Empty();
	AttackRangeSphere->GetOverlappingActors(OverlappedTargets, ACharacter::StaticClass());

	AActor* NearestTarget = nullptr;
	
	
	if (OverlappedTargets.Num() > 0)
	{
		for (AActor* TargetActor : OverlappedTargets)
		{
			if (TargetActor == ControlledMinion) continue;
			
		}
	}
	
	
	
}
