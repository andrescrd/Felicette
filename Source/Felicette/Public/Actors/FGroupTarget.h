// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Support/Enums/FPickedTypeEnum.h"

#include "FGroupTarget.generated.h"

UCLASS()
class FELICETTE_API AFGroupTarget : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFGroupTarget();

protected:

	UPROPERTY()
	class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UChildActorComponent* PickupChild;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UChildActorComponent* TargetChild;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category=Setup)
	TSubclassOf<class AFPickup> PickupClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category=Setup)
	TSubclassOf<class AFPickupTarget> PickupTargetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category=Setup)
	FPickedTypeEnum PickedType;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=Setup)	
	class UDataTable* DataTable;

	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
};
