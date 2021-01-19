// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/FMovableComponent.h"
#include "Components/FRotatorComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Support/Enums/FPickedTypeEnum.h"

#include "FPickup.generated.h"

UCLASS()
class FELICETTE_API AFPickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPickup();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AFDisolver> DisolverClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFRotatorComponent* RotatorComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFMovableComponent* MovableComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FPickedTypeEnum PickedType;

	virtual void BeginPlay() override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FPickedTypeEnum GetPickedType() const;
	void Picked(class AFCharacter* Other);
	void Drop(const FVector EndLocation = FVector::ZeroVector, bool SpawnEmmiter = false);
};
