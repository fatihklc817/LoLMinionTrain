// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMTCharacter.generated.h"

UCLASS()
class LOLMINIONTRAIN_API ALMTCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	
#pragma region Components
	
	/** Top down camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	ACameraActor* TargetCameraActor;

	UPROPERTY()
	class ALMTMinionBase* CurrentTarget;

	/** camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraSpringArmComponent;

#pragma endregion Components

#pragma region Properties

	UPROPERTY(EditDefaultsOnly)
	float AttackRange;

	UPROPERTY()
	FVector TargetLocation;

	FVector AvoidingMoveLocation;

	bool bAvoiding;

	bool bCanAvoid = true;
	FTimerHandle AvoidCooldownTimerHandle;

	void ResetAvoidCooldown();
	
#pragma endregion Properties
	
	
public:
	ALMTCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
	void Attack();

	UFUNCTION()
	bool CheckIsTargetInRange();

	
	// UFUNCTION()
	// void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	UFUNCTION()
	void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
	//getter setter functions
#pragma region GetterSetter
	
	UFUNCTION()
	ACameraActor* GetTargetCameraActor();

	UFUNCTION()
	class ALMTMinionBase* GetCurrentTarget();

	UFUNCTION()
	void SetCurrentTarget(ALMTMinionBase* MinionTarget);

	UFUNCTION()
	void SetTargetLocation(FVector InLocation);
	
	
	
#pragma endregion GetterSetter
	
	

};
