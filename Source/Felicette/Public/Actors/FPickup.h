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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFRotatorComponent* RotatorComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFMovableComponent* MovableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Setup)
	FPickedTypeEnum PickedType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Setup)
	FName MaterialSlotNameGlow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Setup)
	FName MaterialColorParameterName;

	virtual void BeginPlay() override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void SetPickedType(FPickedTypeEnum PickedTypeEnum);
	void SetColor(const FLinearColor Color) const;
	void Picked(class AFCharacter* Other);
	void Dropped();

	UFUNCTION(BlueprintCallable)
	FPickedTypeEnum GetPickedType() const;
	UFUNCTION(BlueprintCallable)
	FLinearColor GetPrimaryColor() const;
};
