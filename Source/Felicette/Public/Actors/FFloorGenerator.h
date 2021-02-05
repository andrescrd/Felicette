// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FBlock.h"
#include "GameFramework/Actor.h"
#include "FFloorGenerator.generated.h"

UCLASS()
class FELICETTE_API AFFloorGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFFloorGenerator();

protected:
	TArray<AActor*> Blocks;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FloorGenerator)
	int MaxX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FloorGenerator)
	int MaxY;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FloorGenerator)
	float Spacing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FloorGenerator)
	TSubclassOf<class AFBlock> BlockClass;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(CallInEditor, Category=FloorGenerator)
	void Generate();
};
