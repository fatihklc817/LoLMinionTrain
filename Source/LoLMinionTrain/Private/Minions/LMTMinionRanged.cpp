// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/LMTMinionRanged.h"

#include "LMTProjectileBase.h"

void ALMTMinionRanged::FireProjectile()
{
	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = this;
	spawnParameters.Instigator = this;
	
	
	bIsAttackOnCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&ALMTMinionBase::ResetAttack,AttackSpeed,false);

	ALMTProjectileBase* Projectile = GetWorld()->SpawnActor<ALMTProjectileBase>(ProjectileClass,GetMesh()->GetSocketLocation("StaffSocket"),FRotator::ZeroRotator,spawnParameters);
	Projectile->SetTargetActor(LastTarget);
	Projectile->SetDamage(Damage);
}
