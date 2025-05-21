// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/LMTGridGenerator.h"

ALMTGridGenerator::ALMTGridGenerator()
{
 	PrimaryActorTick.bCanEverTick = false;

}

void ALMTGridGenerator::BeginPlay()
{
	Super::BeginPlay();

	GenerateGrid();
}

void ALMTGridGenerator::GenerateGrid()
{
	int32 gridNodeSize = GridSizeX * GridSizeY;

	for (int32 x = 0; x < GridSizeX; x++)
	{
		for (int32 y = 0; y < GridSizeY; y++)
		{
			FVector location = GetActorLocation() + FVector(x * CellSize, y * CellSize, GetActorLocation().Z);
			FGridNode NewNode;
			NewNode.Location = location;
			Nodes.Add(NewNode);
			DrawDebugBox(GetWorld(),location,FVector(CellSize*0.5f,CellSize*0.5f,20.f),FColor::Red,true);
		}
	}
}



