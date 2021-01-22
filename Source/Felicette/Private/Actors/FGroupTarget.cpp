// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FGroupTarget.h"

#include "Actors/FPickup.h"
#include "Actors/FPickupTarget.h"
#include "Components/ChildActorComponent.h"


AFGroupTarget::AFGroupTarget()
{
	PickedType = FPickedTypeEnum::DEFAULT;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PickupChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("PickupChild"));
	PickupChild->SetRelativeLocation(FVector(50,50,0));
	PickupChild->SetupAttachment(RootComponent);	
	
	TargetChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("TargetChild"));
	TargetChild->SetRelativeLocation(FVector(-50,50,0));
	TargetChild->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = false;
}

void AFGroupTarget::BeginPlay()
{
	Super::BeginPlay();
}

void AFGroupTarget::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (PickupClass && PickupChild)
	{
		PickupChild->SetChildActorClass(PickupClass);
		PickupChild->CreateChildActor();

		if(AFPickup* Pickup =  Cast<AFPickup>(PickupChild->GetChildActor()))
			Pickup->SetPickedType(PickedType);
	}

	if (TargetChild && PickupTargetClass)
	{
		TargetChild->SetChildActorClass(PickupTargetClass);
		TargetChild->CreateChildActor();

		if(AFPickupTarget* Target =  Cast<AFPickupTarget>(TargetChild->GetChildActor()))
			Target->SetPickedType(PickedType);
	}	
}
