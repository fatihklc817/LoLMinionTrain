// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/LMTWidgetText.h"
#include "LMTPlayerController.generated.h"


enum class ECursorState : uint8
{
	Default,
	Attack
};


class UNiagaraSystem;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class LOLMINIONTRAIN_API ALMTPlayerController : public APlayerController
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditDefaultsOnly,Category= UI )
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	ULMTWidgetText* HUDWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> CursorDefaultWidgetClass;

	UPROPERTY()
	UUserWidget* CursorWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> CursorAttackWidgetClass;

	UPROPERTY()
	UUserWidget* CursorAtkWidget;

	ECursorState CurrentCursorState;


	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MouseLeftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MouseRightClickAction;


	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupInputComponent() override;

	void OnMouseClick();

public:

	void UpdateCsScoreHud(float InValue);
	
};
