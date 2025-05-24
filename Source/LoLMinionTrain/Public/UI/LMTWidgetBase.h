// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LMTWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class LOLMINIONTRAIN_API ULMTWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

public:
	UFUNCTION(BlueprintCallable)
	void SetHealthBar(float percent);
	
};
