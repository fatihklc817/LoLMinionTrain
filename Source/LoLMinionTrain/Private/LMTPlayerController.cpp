// Fill out your copyright notice in the Description page of Project Settings.


#include "LMTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LMTCharacter.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Minions/LMTMinionBase.h"
#include "UI/LMTWidgetText.h"


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

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<ULMTWidgetText>(this,HUDWidgetClass);
		HUDWidget->AddToViewport();
	}
	
	bShowMouseCursor = false;

	if (CursorDefaultWidgetClass)
	{
		CursorWidget = CreateWidget<UUserWidget>(this, CursorDefaultWidgetClass);
		if (CursorWidget)
		{
			CursorWidget->AddToViewport();
			FVector2D MousePosition;
			GetMousePosition(MousePosition.X, MousePosition.Y);
			float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
			FVector2D ScaledMousePosition = MousePosition / ViewportScale;
			CursorWidget->SetPositionInViewport(ScaledMousePosition, false);
		}
	}

	if (CursorAttackWidgetClass)
	{
		CursorAtkWidget = CreateWidget<UUserWidget>(this, CursorAttackWidgetClass);
		if (CursorAtkWidget)
		{
			CursorAtkWidget->SetVisibility(ESlateVisibility::Hidden);
			CursorAtkWidget->AddToViewport();
		}
	}
	
	
	
}

void ALMTPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	ECursorState NewState = ECursorState::Default;
	float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
	
	
	FVector2D MousePosition;
	if (GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		FVector2D ScaledMousePosition = MousePosition / ViewportScale;
		if (CursorWidget)
		{
			CursorWidget->SetPositionInViewport(ScaledMousePosition, false);
		}
		if (CursorAtkWidget)
		{
			CursorAtkWidget->SetPositionInViewport(ScaledMousePosition, false);
		}
	}
	
	FHitResult HitResult;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);
	
	if (bHitSuccessful)
	{
		if (ALMTMinionBase* HitMinion = Cast<ALMTMinionBase>(HitResult.GetActor()))
		{
			if (HitMinion->GetTeam() == ECharTeam::Red)
			{
				NewState = ECursorState::Attack;
			}
		}
	}

	

	if (NewState != CurrentCursorState)
	{
		CurrentCursorState = NewState;

		if (CurrentCursorState == ECursorState::Attack)
		{
			CursorWidget->SetVisibility(ESlateVisibility::Hidden);
			CursorAtkWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CursorWidget->SetVisibility(ESlateVisibility::Visible);
			CursorAtkWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	
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
			if (HitMinion->GetTeam() == ECharTeam::Red)
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
					LMTCharacter->GetMesh()->GetAnimInstance()->Montage_Stop(0.15f);
					LMTCharacter->SetbIsAttacking(false);
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
				LMTCharacter->SetCurrentTarget(nullptr);
				LMTCharacter->GetMesh()->GetAnimInstance()->Montage_Stop(0.15f);
				LMTCharacter->SetbIsAttacking(false);
			}
		}
		
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitResult.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
	
}

void ALMTPlayerController::UpdateCsScoreHud(float InValue)
{
	HUDWidget->SetCsScore(InValue);
}
