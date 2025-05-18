// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/LMTMinionBase.h"

// Sets default values
ALMTMinionBase::ALMTMinionBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALMTMinionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALMTMinionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALMTMinionBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

