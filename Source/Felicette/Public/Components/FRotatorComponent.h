// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FRotatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FELICETTE_API UFRotatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFRotatorComponent();

protected:
	FRotator StartRotation;
	FRotator EndRotation;

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
