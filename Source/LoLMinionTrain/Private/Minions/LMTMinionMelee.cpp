// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/LMTMinionMelee.h"

#include "LMTAttributeComp.h"

void ALMTMinionMelee::ApplyMeleeDamageToTarget()
{
	ULMTAttributeComp* targetAttribute = LastTarget->GetComponentByClass<ULMTAttributeComp>();
	if (targetAttribute)
	{
		targetAttribute->TakeDamage(Damage);
		
		bIsAttackOnCooldown = true;
		GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&ALMTMinionBase::ResetAttack,AttackSpeed,false);
	}
}
