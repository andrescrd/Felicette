// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FRotatorComponent.h"

#include "Components/TimelineComponent.h"

UFRotatorComponent::UFRotatorComponent()
{
	DeltaRotation = FFloatRange::Inclusive(-180, 180);
	TimelineTime = FFloatRange::Inclusive(.5, 3);
	bAutoActivate = true;

	RotatorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("RotatorTimeline"));

	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UFRotatorComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupTimeline();
	
	if (bAutoActivate)
		PlayTimeline();
}

void UFRotatorComponent::SetupTimeline()
{
	if (!Curve)
		return;

	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnTimelineHandler"));

	FOnTimelineEvent TimelineFinished;
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinish"));

	RotatorTimeline->AddInterpFloat(Curve, TimelineCallback);
	RotatorTimeline->SetTimelineFinishedFunc(TimelineFinished);

	RotatorTimeline->SetIgnoreTimeDilation(true);
	RotatorTimeline->SetLooping(false);
}

void UFRotatorComponent::PlayTimeline()
{
	GetRotationForTimeline();
	RotatorTimeline->PlayFromStart();
}

void UFRotatorComponent::GetRotationForTimeline()
{
	AActor* CurrentActor = GetOwner();

	if (CurrentActor)
	{
		StartRotation = CurrentActor->GetActorRotation();
		EndRotation = StartRotation;
		EndRotation.Yaw += FMath::RandRange(DeltaRotation.GetLowerBound().GetValue(), DeltaRotation.GetUpperBound().GetValue());
		const float NewRate = 1 / FMath::RandRange(TimelineTime.GetLowerBound().GetValue(), TimelineTime.GetUpperBound().GetValue());;
		RotatorTimeline->SetPlayRate(NewRate);
	}
}

void UFRotatorComponent::OnTimelineHandler(float Value)
{
	AActor* CurrentActor = GetOwner();

	if (CurrentActor)
		CurrentActor->SetActorRotation(FMath::Lerp(StartRotation, EndRotation, Value));
}

void UFRotatorComponent::OnTimelineFinish() { PlayTimeline(); }

void UFRotatorComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	PlayTimeline();
}

void UFRotatorComponent::Deactivate()
{
	Super::Deactivate();
	RotatorTimeline->Deactivate();
}
