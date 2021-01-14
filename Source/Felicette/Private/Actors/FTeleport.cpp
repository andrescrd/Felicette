// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FTeleport.h"

// Sets default values
AFTeleport::AFTeleport()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	RootComponent = MeshComponent;

	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AFTeleport::BeginPlay()
{
	Super::BeginPlay();
	
}