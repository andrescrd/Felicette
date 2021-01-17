// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickupTarget.h"

#include "Engine/EngineTypes.h"

// Sets default values
AFPickupTarget::AFPickupTarget()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = MeshComponent;
	
	PrimaryActorTick.bCanEverTick = false;

}
void AFPickupTarget::BeginPlay()
{
	Super::BeginPlay();	
}
