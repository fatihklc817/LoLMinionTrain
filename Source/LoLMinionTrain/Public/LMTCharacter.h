// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMTCharacter.generated.h"

UCLASS()
class LOLMINIONTRAIN_API ALMTCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region Components

private:
	/** Top down camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	ACameraActor* TargetCameraActor;

	
#pragma endregion Components
	
	
public:
	// Sets default values for this character's properties
	ALMTCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	FORCEINLINE ACameraActor* GetTargetCameraActor() const { return TargetCameraActor; };	

};
