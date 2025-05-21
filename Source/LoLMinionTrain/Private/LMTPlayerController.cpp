// Fill out your copyright notice in the Description page of Project Settings.


#include "LMTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LMTCharacter.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Minions/LMTMinionBase.h"


void ALMTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// if (ACameraActor* TargetCamera = Cast<ALMTCharacter>(GetPawn())->GetTargetCameraActor())
	// {
	// 	SetViewTarget(TargetCamera);
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("target camera alinamadi"));
	// }

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	bShowMouseCursor = true;
	
	
	
}

void ALMTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// move
		EnhancedInputComponent->BindAction(MouseRightClickAction, ETriggerEvent::Started, this, &ALMTPlayerController::OnMouseClick);
	

	
	}

	
}

void ALMTPlayerController::OnMouseClick()
{
	ALMTCharacter* LMTCharacter = Cast<ALMTCharacter>(GetPawn());
	
	FHitResult HitResult;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);
	
	if (bHitSuccessful)
	{
		if (ALMTMinionBase* HitMinion = Cast<ALMTMinionBase>(HitResult.GetActor()))
		{
			if (HitMinion->GetMinionTeam() == EMinionTeam::Enemy)
			{
				UE_LOG(LogTemp, Warning, TEXT("hit minion name : %s"),*HitMinion->GetName());
				LMTCharacter->SetCurrentTarget(HitMinion);
				if (LMTCharacter->CheckIsTargetInRange())
				{
					LMTCharacter->Attack();
				}
				else
				{
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,HitResult.Location);
					LMTCharacter->SetTargetLocation(HitResult.Location);
				}
				
			}
		}
		else
		{
			FNavLocation NavLocation;
			UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
			if (NavSys && NavSys->ProjectPointToNavigation(HitResult.Location, NavLocation))
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,NavLocation);
				LMTCharacter->SetTargetLocation(HitResult.Location);
			}
		}
		
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitResult.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
	
}
