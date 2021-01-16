// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickup.h"


#include "Components/FRotatorComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
AFPickup::AFPickup()
{	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCanEverAffectNavigation(false);
	RootComponent = MeshComponent;

	RotatorComponent = CreateDefaultSubobject<UFRotatorComponent>(TEXT("RotatorComponent"));

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPickup::BeginPlay()
{
	Super::BeginPlay();
}