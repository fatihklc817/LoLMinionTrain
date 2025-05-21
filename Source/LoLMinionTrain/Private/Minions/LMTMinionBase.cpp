// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/LMTMinionBase.h"

#include "NavModifierComponent.h"
#include "Components/CapsuleComponent.h"


ALMTMinionBase::ALMTMinionBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// NavModifierComponent = CreateDefaultSubobject<UNavModifierComponent>("NavModifierComponent");
	// NavModifierComponent->FailsafeExtent = FVector(5.f,5.f,5.f);
	// NavModifierComponent->SetActive(false);
	// NavModifierComponent->SetComponentTickEnabled(false);

	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
}


void ALMTMinionBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void ALMTMinionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALMTMinionBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

