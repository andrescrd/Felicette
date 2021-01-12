// Fill out your copyright notice in the Description page of Project Settings.


#include "Felicette/Public/Actors/FBlock.h"


#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AFBlock::AFBlock()
{
	bActive = true;
	OffsetZ = -256;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(32,32,64));
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFBlock::BeginPlay()
{
	Super::BeginPlay();
}

void AFBlock::NotifyActorEndOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Green, TEXT("Overlap") );
	
	if (bActive && OtherActor->IsA(ACharacter::StaticClass()))
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z += OffsetZ;
		SetActorLocation(NewLocation);

		bActive = false;
	}
}

void AFBlock::NotifyActorBeginOverlap(AActor* OtherActor)
{	
	
}
