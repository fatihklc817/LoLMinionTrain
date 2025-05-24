// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMTProjectileBase.generated.h"

UCLASS()
class LOLMINIONTRAIN_API ALMTProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed;
	
	UPROPERTY(VisibleAnywhere)
	AActor* TargetActor;

	UPROPERTY(VisibleAnywhere)
	float Damage;

	
	
public:	
	// Sets default values for this actor's properties
	ALMTProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetTargetActor(AActor* InActor);

	UFUNCTION()
	void SetDamage(float InDamage);

};

