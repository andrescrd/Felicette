// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPickup.generated.h"

UCLASS()
class FELICETTE_API AFPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPickup();

protected:
	FRotator StartRotation;
	FRotator EndRotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTimelineComponent* TimelineComponent;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCurveFloat* Curve;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFloatRange DeltaRotation;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)	
	FFloatRange TimelineTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)	
	bool bEnableMovement;	

	virtual void BeginPlay() override;
	void SetupAndPlayTimeline();
	void GetRotationForTimeline();

	UFUNCTION()
	void OnTimelineHandler(float Value);
	UFUNCTION()
	void OnTimelineFinish();
	
public:
};
