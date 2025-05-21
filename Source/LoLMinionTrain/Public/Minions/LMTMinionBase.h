// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMTMinionBase.generated.h"

UENUM(BlueprintType)
enum class EMinionTeam : uint8
{
	Ally UMETA(DisplayName = "Ally"),
	Enemy UMETA(DisplayName = "Enemy")
};

UCLASS()
class LOLMINIONTRAIN_API ALMTMinionBase : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	EMinionTeam MinionTeam;

	// UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	// class UNavModifierComponent* NavModifierComponent;
	
public:
	// Sets default values for this character's properties
	ALMTMinionBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	FORCEINLINE EMinionTeam GetMinionTeam() const { return MinionTeam; };

};
