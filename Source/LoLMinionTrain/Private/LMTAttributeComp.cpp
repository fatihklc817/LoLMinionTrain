// Fill out your copyright notice in the Description page of Project Settings.


#include "LMTAttributeComp.h"

#include "Minions/LMTMinionBase.h"


ULMTAttributeComp::ULMTAttributeComp()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}



void ULMTAttributeComp::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}

bool ULMTAttributeComp::TakeDamage(float DamageAmount)
{
	float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f,MaxHealth);
	
	if (CurrentHealth != OldHealth)
	{
		OnHealthChanged.Broadcast(CurrentHealth / MaxHealth);
		if (CurrentHealth <= 0)
		{
			ALMTMinionBase* ownerMinion = Cast<ALMTMinionBase>(GetOwner());
			if (ownerMinion)
			{
				ownerMinion->PlayDeathAnim();
			}

			//GetOwner()->Destroy();
		}
		return true;
		
	}
	else
	{
		return false;
	}
}

//getter setter
void ULMTAttributeComp::SetHealth(float InHealth)
{
	CurrentHealth = InHealth;
}

float ULMTAttributeComp::GetHealth()
{
	return CurrentHealth;
}

float ULMTAttributeComp::GetMaxHealth()
{
	return MaxHealth;
}






