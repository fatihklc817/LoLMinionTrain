// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LMTWidgetText.h"

#include "Components/TextBlock.h"

void ULMTWidgetText::SetCsScore(float inValue)
{
	FString ScoreText = FString::Printf(TEXT("CS SCORE : %d"), FMath::RoundToInt(inValue));
	CsScore->SetText(FText::FromString(ScoreText));
}
