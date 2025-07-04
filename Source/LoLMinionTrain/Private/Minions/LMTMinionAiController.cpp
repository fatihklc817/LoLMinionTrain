// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/LMTMinionAiController.h"

#include "AI/NavigationSystemBase.h"
#include "Components/SphereComponent.h"
#include "Minions/LMTMinionBase.h"

void ALMTMinionAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledMinion = Cast<ALMTMinionBase>(GetPawn());
	
}

void ALMTMinionAiController::BeginPlay()
{
	Super::BeginPlay();
	bMoving = false;

	
	
	UE_LOG(LogTemp, Warning, TEXT("ai controller begin "));

	// Detect işlemi
	FTimerHandle CheckTargetHandle;
	GetWorld()->GetTimerManager().SetTimer(CheckTargetHandle, this, &ALMTMinionAiController::CheckOverlappingTargets, 0.5f, true);
}

void ALMTMinionAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	bool bGoingToTarget = false;
	
	if (ControlledMinion == nullptr)
	{
		return;
	}

	if (ControlledMinion->GetBAvoiding())
	{
		return;
	}
	
	if (CurrentTarget)
	{
		if (ControlledMinion->CheckTargetIsInRange())
		{
			StopMovement();
			bMoving = false;
			bGoingToTarget = false;
			ControlledMinion->SetTarget(CurrentTarget);
			ControlledMinion->Attack();
		}
		else
		{
			if (!bGoingToTarget && !ControlledMinion->GetbIsAttacking())
			{
				MoveToLocation(CurrentTarget->GetActorLocation());
				ControlledMinion->SetTargetLocation(CurrentTarget->GetActorLocation());
				bGoingToTarget = true;
				bMoving = true;
			}
		}
		
	}
	else
	{
		if (!bMoving)
		{
			//eğer karakterin location ı ile lanedeki projected olan location arası mesafe 75 dan az ise lanedeki projected location a git
			float dist = FVector::Dist(ControlledMinion->GetActorLocation(), GetNearestLocationOnLane());
			if ( dist <= 150.f)
			{
				MoveToLaneEnd();
			}
			else
			{
				FVector NearestLocation = GetNearestLocationOnLane();
				//DrawDebugSphere(GetWorld(), NearestLocation, 25.f, 12, FColor::Green, true);
				MoveToLocation(NearestLocation);
				ControlledMinion->SetTargetLocation(NearestLocation);
			}
		}
	}
}

void ALMTMinionAiController::MoveToLaneEnd()
{
	if (bMoving)
	{
		return;
	}
	
	FVector ForwardPoint = ControlledMinion->GetActorLocation() + ControlledMinion->GetActorForwardVector() * 5000;
	MoveToLocation(ControlledMinion->LaneEnd);
	ControlledMinion->SetTargetLocation(ControlledMinion->LaneEnd);
	bMoving = true;

	
}

void ALMTMinionAiController::CheckOverlappingTargets()
{
	//
	// // Hedefi kontrol et
	// if (CurrentTarget)
	// {
	// 	if (CurrentTarget->IsPendingKill()||  !ControlledMinion->GetAttackRangeSphere()->IsOverlappingActor(CurrentTarget) )
	// 	{
	// 		CurrentTarget = nullptr; // Target düştü veya menzil dışı
	// 		StopMovement();
	// 		bMoving = false;
	// 	}
	// }
	//
	// if (!CurrentTarget)
	// {
	// 	USphereComponent* AttackRangeSphere = ControlledMinion->GetAttackRangeSphere();
	// 	OverlappedTargets.Empty();
	// 	
	// 	AttackRangeSphere->GetOverlappingActors(OverlappedTargets, ACharacter::StaticClass());
	//
	// 	float NearestDistance = AttackRangeSphere->GetScaledSphereRadius();
	// 	ALMTBaseCharacter* NearestTarget = nullptr;
	// 	
	// 	
	// 	if (OverlappedTargets.Num() > 0)
	// 	{
	// 		for (AActor* TargetActor : OverlappedTargets)
	// 		{
	// 			if (TargetActor == ControlledMinion) continue;
	// 			if (ALMTBaseCharacter* TargetbaseChar = Cast<ALMTBaseCharacter>(TargetActor))
	// 			{
	// 				//UE_LOG(LogTemp, Warning, TEXT("bi charla overlap etti"));
	// 				if (TargetbaseChar->GetTeam() != ControlledMinion->GetTeam())
	// 				{
	// 					UE_LOG(LogTemp, Warning, TEXT("düsmandur daa"));
	// 					const float Distance = FVector::Dist(ControlledMinion->GetActorLocation(), TargetbaseChar->GetActorLocation());
	//
	// 					if (Distance <= NearestDistance)
	// 					{
	// 						NearestDistance = Distance;
	// 						NearestTarget = TargetbaseChar;
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	//
	// 	if (NearestTarget != nullptr)
	// 	{
	// 		CurrentTarget = NearestTarget;
	// 		ControlledMinion ->SetTarget(CurrentTarget);
	// 	}
	// 	
	// }
	//
	//

	
		USphereComponent* AttackRangeSphere = ControlledMinion->GetAttackRangeSphere();
		OverlappedTargets.Empty();
	
		AttackRangeSphere->GetOverlappingActors(OverlappedTargets, ACharacter::StaticClass());

		float NearestDistance = AttackRangeSphere->GetScaledSphereRadius();
		ALMTBaseCharacter* NearestTarget = nullptr;

		for (AActor* TargetActor : OverlappedTargets)
		{
			if (TargetActor == ControlledMinion) continue;

			if (ALMTBaseCharacter* TargetBaseChar = Cast<ALMTBaseCharacter>(TargetActor))
			{
				if (TargetBaseChar->GetTeam() != ControlledMinion->GetTeam())
				{
					const float Distance = FVector::Dist(ControlledMinion->GetActorLocation(), TargetBaseChar->GetActorLocation());
					if (Distance <= NearestDistance)
					{
						NearestDistance = Distance;
						NearestTarget = TargetBaseChar;
					}
				}
			}
		}

		// Eğer elimizde yeni bir target varsa ve CurrentTarget yoksa veya bu daha yakınsa ona geç
		if (NearestTarget)
		{
			// Eğer zaten başka bir hedef varsa ve bu hedef başkaysa ona geç
			if (CurrentTarget != NearestTarget)
			{
				UE_LOG(LogTemp, Warning, TEXT("Target değiştirildi: %s -> %s"), 
					*GetNameSafe(CurrentTarget), 
					*GetNameSafe(NearestTarget));

				CurrentTarget = NearestTarget;
				ControlledMinion->SetTarget(CurrentTarget);
			}
		}
		else
		{
			// Eğer menzilde kimse kalmadıysa hedefi sıfırla
			if (CurrentTarget)
			{
				CurrentTarget = nullptr;
				ControlledMinion->SetTarget(nullptr);
				StopMovement();
				bMoving = false;
			}
		}
	
	
}

FVector ALMTMinionAiController::GetNearestLocationOnLane()
{
	if (ControlledMinion)
	{
		FVector LaneStart = ControlledMinion->LaneStart;
		FVector LaneEnd = ControlledMinion->LaneEnd;

		FVector MinionLocation = ControlledMinion->GetActorLocation();
		FVector LaneDirection = (LaneEnd - LaneStart).GetSafeNormal();
		float Projection = FVector::DotProduct(MinionLocation-LaneStart, LaneDirection);

		FVector nearestLocation = LaneStart + LaneDirection * Projection;

		FVector OffsetPoint = nearestLocation + LaneDirection * 100.f; // 100 units offset from the lane start
		
		return OffsetPoint;
	}
	
	return FVector::ZeroVector;
}
