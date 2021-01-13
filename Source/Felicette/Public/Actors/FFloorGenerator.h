// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY()
	class UInstancedStaticMeshComponent* InstancedStaticMeshComponent;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxY;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Spacing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMesh* StaticMesh;

	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;
};
