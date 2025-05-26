// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMTMinionBase.generated.h"

UENUM(BlueprintType)
enum class EMinionTeam : uint8
{
	Ally UMETA(DisplayName = "Blue"),
	Enemy UMETA(DisplayName = "Red")
};

UCLASS()
class LOLMINIONTRAIN_API ALMTMinionBase : public ACharacter
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

	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	EMinionTeam MinionTeam;



public:
	
	ALMTMinionBase();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChanged(float NewHealthPercent);

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	FORCEINLINE EMinionTeam GetMinionTeam() const { return MinionTeam; };

	USphereComponent* GetAttackRangeSphere();

};
