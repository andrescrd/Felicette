// Fill out your copyright notice in the Description page of Project Settings.


#include "Felicette/Public/Actors/FBlock.h"
#include "Actors/FPickup.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFBlock::AFBlock()
{
	bActive = true;
	OffsetZ = -256;
	TimelineTime = 3;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(32, 32, 64));
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));

	PrimaryActorTick.bCanEverTick = false;
}

void AFBlock::BeginPlay()
{
	Super::BeginPlay();
	SetupTimeline();

	//Setup primary material
	const int32 MaterialIndex = MeshComponent->GetMaterialIndex(MaterilaSlotName);
	MaterialPrimary = MeshComponent->GetMaterial(MaterialIndex);
}

void AFBlock::SetupTimeline()
{
	if (!Curve)
		return;

	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnTimelineHandler"));
	TimelineComponent->AddInterpFloat(Curve, TimelineCallback);

	const float NewRate = 1 / TimelineTime;
	TimelineComponent->SetPlayRate(NewRate);
	TimelineComponent->SetIgnoreTimeDilation(true);

	StartLocation = GetActorLocation();
	EndLocation = StartLocation;
	EndLocation.Z += OffsetZ;
}

void AFBlock::OnTimelineHandler(const float Output) { SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Output)); }

void AFBlock::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (bActive && OtherActor->IsA(ACharacter::StaticClass()))
	{
		TimelineComponent->Play();
		bActive = false;

		int32 MaterialIndex = MeshComponent->GetMaterialIndex(MaterilaSlotName);
		if (MaterialSecondary)
			MeshComponent->SetMaterial(MaterialIndex, MaterialSecondary);

		MaterialIndex = MeshComponent->GetMaterialIndex(MaterilaSlotNameGlow);
		if (MaterialSecondary)
			MeshComponent->SetMaterial(MaterialIndex, MaterialSecondary);

		if(ActiveSound)
			UGameplayStatics::PlaySound2D(this, ActiveSound);
	}
}

void AFBlock::NotifyActorBeginOverlap(AActor* OtherActor) { }

bool AFBlock::IsValid()
{
	// TODO: check if location is valid to move
	return true;
}

bool AFBlock::IsActive() const { return bActive; }

void AFBlock::NotifyActorBeginCursorOver()
{
	if (IsValid() && !bIsHighlighted && MaterialHeiglight && bActive)
	{
		const int32 MaterialIndex = MeshComponent->GetMaterialIndex(MaterilaSlotName);
		MeshComponent->SetMaterial(MaterialIndex, MaterialHeiglight);
		bIsHighlighted = true;
	}
}

void AFBlock::NotifyActorEndCursorOver()
{
	if (bIsHighlighted && MaterialPrimary && bActive)
	{
		const int32 MaterialIndex = MeshComponent->GetMaterialIndex(MaterilaSlotName);
		MeshComponent->SetMaterial(MaterialIndex, MaterialPrimary);
		bIsHighlighted = false;
	}
}

bool AFBlock::HasItemOverlapped() const
{
	TArray<AActor*> OverlappingActors;
	BoxComponent->GetOverlappingActors(OverlappingActors, AFPickup::StaticClass());

	return OverlappingActors.Num() > 0;
}
