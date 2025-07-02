// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LMTBaseCharacter.h"
#include "GameFramework/Character.h"
#include "LMTMinionBase.generated.h"



UCLASS()
class LOLMINIONTRAIN_API ALMTMinionBase : public ALMTBaseCharacter
{
	GENERATED_BODY()

#pragma region Components
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="Attribute")
	class ULMTAttributeComp* AttributeComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	class UWidgetComponent* HealthBarWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	class USphereComponent* AttackRangeSphere;
	
#pragma endregion

	
	
protected:
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	float Damage;
	
	UPROPERTY(VisibleAnywhere, Category="Attack")
	FTimerHandle AttackTimer;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	float AttackSpeed;
	
	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsAttackOnCooldown;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsAttacking;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	float AttackRange;
	
	UPROPERTY()
	class ALMTBaseCharacter* CurrentTarget;

	UPROPERTY()
	ALMTBaseCharacter* LastTarget;

	FVector AvoidingMoveLocation;

	UPROPERTY(VisibleAnywhere)
	bool bAvoiding;

	bool bCanAvoid = true;
	FTimerHandle AvoidCooldownTimerHandle;

	void ResetAvoidCooldown();

	FVector TargetLocation;
	

public:
	// LMTMinionBase.h veya LMTMinionAiController.h
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LaneStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LaneEnd;


public:
	
	ALMTMinionBase();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChanged(float NewHealthPercent);

	UFUNCTION()
	void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	virtual void Tick(float DeltaSeconds) override;

public:	

	

	USphereComponent* GetAttackRangeSphere();
	
	UFUNCTION()
	void Attack();
	
	UFUNCTION()
	void SetTarget(ALMTBaseCharacter* InTarget);

	UFUNCTION(BlueprintCallable)
	void ResetAttack();

	UFUNCTION()
	bool CheckTargetIsInRange();

	UFUNCTION()
	bool GetbIsAttacking() const { return bIsAttacking; }

	UFUNCTION()
	void SetTargetLocation(FVector InTargetLocation);

	UFUNCTION()
	bool GetBAvoiding();

};
