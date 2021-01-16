// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FRotatorComponent.h"

#include "Components/TimelineComponent.h"

UFRotatorComponent::UFRotatorComponent()
{
	DeltaRotation = FFloatRange::Inclusive(-180, 180);
	TimelineTime = FFloatRange::Inclusive(.5, 3);
	bEnableMovement = true;

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));

	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UFRotatorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bEnableMovement)
		SetupAndPlayTimeline();
}

void UFRotatorComponent::SetupAndPlayTimeline()
{
	if (!Curve)
		return;

	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnTimelineHandler"));

	FOnTimelineEvent TimelineFinished;
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinish"));

	TimelineComponent->AddInterpFloat(Curve, TimelineCallback);
	TimelineComponent->SetTimelineFinishedFunc(TimelineFinished);

	TimelineComponent->SetIgnoreTimeDilation(true);
	TimelineComponent->SetLooping(false);

	GetRotationForTimeline();
	TimelineComponent->Play();
}

void UFRotatorComponent::GetRotationForTimeline()
{
	AActor* CurrentActor = GetOwner();

	if (CurrentActor)
	{
		StartRotation = CurrentActor->GetActorRotation();
		EndRotation = StartRotation;
		EndRotation.Yaw = FMath::RandRange(DeltaRotation.GetLowerBound().GetValue(), DeltaRotation.GetUpperBound().GetValue());
		const float NewRate = 1 / FMath::RandRange(TimelineTime.GetLowerBound().GetValue(), TimelineTime.GetUpperBound().GetValue());;
		TimelineComponent->SetPlayRate(NewRate);
	}
}

void UFRotatorComponent::OnTimelineHandler(float Value)
{
	AActor* CurrentActor = GetOwner();

	if (CurrentActor)
		CurrentActor->SetActorRotation(FMath::Lerp(StartRotation, EndRotation, Value));
}

void UFRotatorComponent::OnTimelineFinish()
{
	GetRotationForTimeline();
	TimelineComponent->PlayFromStart();
}
