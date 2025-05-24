// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMTAttributeComp.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealthPercent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOLMINIONTRAIN_API ULMTAttributeComp : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	float MaxHealth;
public:
	FOnHealthChanged OnHealthChanged;
	
public:	
	ULMTAttributeComp();
	
protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	bool TakeDamage(float DamageAmount);
	
#pragma region GetterSetter

public:
	void SetHealth(float InHealth);
	float GetHealth();
	
	float GetMaxHealth();
	
#pragma endregion
		
};
