// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FPickup.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "FPickupTarget.generated.h"

UCLASS()
class FELICETTE_API AFPickupTarget : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPickupTarget();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FPickedTypeEnum PickedType;

	virtual void BeginPlay() override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickedCollected(AFPickup* OtherActor);
};
