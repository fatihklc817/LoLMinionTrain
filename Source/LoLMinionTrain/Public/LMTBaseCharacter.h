// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMTBaseCharacter.generated.h"


UENUM(BlueprintType)
enum class ECharTeam : uint8
{
	Blue UMETA(DisplayName = "Blue"),
	Red UMETA(DisplayName = "Red")
};

UCLASS()
class LOLMINIONTRAIN_API ALMTBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ALMTBaseCharacter();

protected:
	UPROPERTY(EditDefaultsOnly)
	ECharTeam CharTeam;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ECharTeam GetTeam() const { return CharTeam; }

};
