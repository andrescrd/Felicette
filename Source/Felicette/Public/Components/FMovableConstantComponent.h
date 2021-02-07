// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FMovableConstantComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FELICETTE_API UFMovableConstatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFMovableConstatComponent();

protected:
	FVector StartLocation;
	FVector EndLocation;
	class UTimelineComponent* MovableTimeline;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCurveFloat* Curve;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float OffsetZ;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)	
	FFloatRange TimelineTime;

	virtual void BeginPlay() override;
	void SetupTimeline();
	void PlayTimeline();
	void GetLocationForTimeline();

	UFUNCTION()
    void OnTimelineHandler(float Value);
	UFUNCTION()
    void OnTimelineFinish();

public:
	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;

};
