// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FTeleport.h"

#include "Character/FCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AFTeleport::AFTeleport()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCOmponent"));
	BoxComponent->SetBoxExtent(FVector(8,8,32));
	RootComponent = BoxComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFTeleport::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFTeleport::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(AFCharacter* Character = Cast<AFCharacter>(OtherActor))
		Character->StartFX();
}
