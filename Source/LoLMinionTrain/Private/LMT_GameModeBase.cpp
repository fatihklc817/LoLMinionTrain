// Fill out your copyright notice in the Description page of Project Settings.


#include "LMT_GameModeBase.h"

#include "Minions/LMTMinionBase.h"

void ALMT_GameModeBase::BeginPlay()
{
	Super::BeginPlay();


	// spawn işlemi
	FTimerHandle waveSpawnHandle;
	GetWorld()->GetTimerManager().SetTimer(waveSpawnHandle, this, &ALMT_GameModeBase::SpawnMinionWaves, waveSpawnSecond, true);
	SpawnMinionWaves();
	
	
} 

void ALMT_GameModeBase::SpawnMinionWaves()
{

	//MeleeMinionSpawnCount = 3;
	BlueMeleeMinionSpawnCount= 3;
	RedMeleeMinionSpawnCount= 3;
	
	//RangedMinionSpawnCount = 3;
	BlueRangedMinionSpawnCount= 3;
	RedRangedMinionSpawnCount= 3;

	
	
	GetWorld()->GetTimerManager().ClearTimer(MinionSpawnHandle);
	GetWorld()->GetTimerManager().SetTimer(MinionSpawnHandle, this, &ALMT_GameModeBase::SpawnNextMinion, 1.f, true);
		
	
	
	

	
}

void ALMT_GameModeBase::SpawnNextMinion()
{

	
	// if (MeleeMinionSpawnCount >0 )
	// {
	// 	FActorSpawnParameters SpawnParams;
	// 	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// 	GetWorld()->SpawnActor<ALMTMinionBase>(RedMeleeMinionClass, FVector(0.f,0.f,500.f), FRotator(0.f,0.f,0.f), SpawnParams);
	// 	GetWorld()->SpawnActor<ALMTMinionBase>(BlueMeleeMinionClass, FVector(0.f,0.f,500.f), FRotator(0.f,0.f,0.f), SpawnParams);
	//
	// 	MeleeMinionSpawnCount--;
	// 	return;
	// }
	
	if (BlueMeleeMinionSpawnCount > 0)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<ALMTMinionBase>(BlueMeleeMinionClass, FVector(0.f,0.f,500.f), FRotator(0.f,0.f,0.f), SpawnParams);

		BlueMeleeMinionSpawnCount--;
	}
	
	if (RedMeleeMinionSpawnCount > 0)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<ALMTMinionBase>(RedMeleeMinionClass, FVector(0.f,0.f,500.f), FRotator(0.f,0.f,0.f), SpawnParams);

		RedMeleeMinionSpawnCount--;
		return;
	}
	
	
	// if (RangedMinionSpawnCount > 0)
	// {
	// 	FActorSpawnParameters SpawnParams;
	// 	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// 	GetWorld()->SpawnActor<ALMTMinionBase>(RedRangedMinionClass, FVector(0.f,0.f,500.f), FRotator(0.f,0.f,0.f), SpawnParams);
	// 	GetWorld()->SpawnActor<ALMTMinionBase>(BlueRangedMinionClass, FVector(0.f,0.f,500.f), FRotator(0.f,0.f,0.f), SpawnParams);
	//
	// 	RangedMinionSpawnCount--;
	// 	return;
	// }

	if (BlueRangedMinionSpawnCount > 0)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<ALMTMinionBase>(BlueRangedMinionClass, FVector(0.f,0.f,500.f), FRotator(0.f,0.f,0.f), SpawnParams);

		BlueRangedMinionSpawnCount--;
	}

	if (RedRangedMinionSpawnCount > 0)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<ALMTMinionBase>(RedRangedMinionClass, FVector(0.f,0.f,500.f), FRotator(0.f,0.f,0.f), SpawnParams);

		RedRangedMinionSpawnCount--;
		return;
	}

	
	GetWorld()->GetTimerManager().ClearTimer(MinionSpawnHandle);
	
	
}

void ALMT_GameModeBase::IncrementCsScore()
{
	CsScore++;
}

float ALMT_GameModeBase::GetCsScore()
{
	return CsScore;
}
