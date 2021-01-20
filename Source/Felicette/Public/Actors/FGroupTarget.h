// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	class AFPickup* Pickup;
	UPROPERTY()	
	class AFPickupTarget* Target;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AFPickup> PickupClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AFPickupTarget> PickupTargetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)    	
	class UChildActorComponent* Weapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USceneComponent* Root;

	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void PostInitProperties() override;
};
