// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FMovableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FELICETTE_API UFMovableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFMovableComponent();

protected:
	FVector StartLocation;
	FVector EndLocation;
	class UTimelineComponent* MovableTimeline;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCurveFloat* Curve;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFloatRange OffsetZ;	
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
