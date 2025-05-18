// Fill out your copyright notice in the Description page of Project Settings.


#include "LMTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LMTCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraActor.h"

void ALMTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ACameraActor* TargetCamera = Cast<ALMTCharacter>(GetPawn())->GetTargetCameraActor())
	{
		SetViewTarget(TargetCamera);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("target camera alinamadi"));
	}

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

	FHitResult HitResult;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);

	if (bHitSuccessful)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,HitResult.Location);
	}
	
}
