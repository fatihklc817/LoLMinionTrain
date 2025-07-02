// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LMTBaseCharacter.h"
#include "GameFramework/Character.h"
#include "LMTCharacter.generated.h"

UCLASS()
class LOLMINIONTRAIN_API ALMTCharacter : public ALMTBaseCharacter
{
	GENERATED_BODY()

protected:
	
#pragma region Components
	
	/** Top down camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	ACameraActor* TargetCameraActor;
	
	/** camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	class ULMTAttributeComp* AttributeComp;

#pragma endregion Components

	
#pragma region Properties

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TArray<UAnimMontage*> AttackMontages;
	
	UPROPERTY(EditDefaultsOnly ,Category="Attack")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	float Damage;
	
	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TSubclassOf<class ALMTProjectileBase> ProjectileClass;

	
	UPROPERTY(VisibleAnywhere, Category="Attack")
	FTimerHandle AttackTimer;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	float AttackSpeed;
	
	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsAttackOnCooldown;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsAttacking;

	UPROPERTY()
	class ALMTMinionBase* CurrentTarget;

	UPROPERTY()
	ALMTMinionBase* LastTarget;

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

	UFUNCTION(BlueprintCallable)
	void FireProjectile();

	UFUNCTION(BlueprintCallable)
	void ResetAttack();

	UFUNCTION()
	void SetbIsAttacking(bool InValue);
	
	// UFUNCTION()
	// void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	UFUNCTION()
	void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
	//getter setter functions
#pragma region GetterSetter
	
	UFUNCTION()
	ACameraActor* GetTargetCameraActor();

	UFUNCTION(BlueprintPure)
	class ALMTMinionBase* GetCurrentTarget();

	UFUNCTION(BlueprintCallable)
	void SetCurrentTarget(ALMTMinionBase* MinionTarget);

	UFUNCTION()
	void SetTargetLocation(FVector InLocation);
	
	
	
#pragma endregion GetterSetter
	
	

};
