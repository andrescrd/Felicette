// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickup.h"

// Sets default values
AFPickup::AFPickup()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCanEverAffectNavigation(false);	
	RootComponent = MeshComponent;
	
	
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFPickup::BeginPlay()
{
	Super::BeginPlay();
	
}