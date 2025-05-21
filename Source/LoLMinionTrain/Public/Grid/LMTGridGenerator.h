// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMTGridGenerator.generated.h"

USTRUCT()
struct FGridNode
{
	GENERATED_BODY()

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	TArray<int32> Neighbors;

	FGridNode() : Location(FVector::ZeroVector) {};
	
};

UCLASS()
class LOLMINIONTRAIN_API ALMTGridGenerator : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true), Category="Grid")
	float CellSize;
	
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true), Category="Grid")
	int32 GridSizeX;

	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true), Category="Grid")
	int32 GridSizeY;
	
	UPROPERTY()
	TArray<FGridNode> Nodes;
	
public:	

	ALMTGridGenerator();

protected:
	
	virtual void BeginPlay() override;


	UFUNCTION()
	void GenerateGrid();


};
