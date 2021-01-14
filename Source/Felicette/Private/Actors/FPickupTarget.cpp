// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickupTarget.h"

// Sets default values
AFPickupTarget::AFPickupTarget()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	PrimaryActorTick.bCanEverTick = false;

}
void AFPickupTarget::BeginPlay()
{
	Super::BeginPlay();	
}
