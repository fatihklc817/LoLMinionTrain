// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LMTWidgetText.generated.h"

/**
 * 
 */
UCLASS()
class LOLMINIONTRAIN_API ULMTWidgetText : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CsScore;

public:

	UFUNCTION(BlueprintCallable)
	void SetCsScore(float inValue);
	
};
