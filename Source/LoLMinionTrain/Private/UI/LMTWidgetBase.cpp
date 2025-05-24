// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LMTWidgetBase.h"

#include "Components/ProgressBar.h"

void ULMTWidgetBase::SetHealthBar(float percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(percent);
	}
}
