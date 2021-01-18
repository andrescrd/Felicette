// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickupTarget.h"


#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"

// Sets default values
AFPickupTarget::AFPickupTarget()
{
	PickedType = FPickedTypeEnum::DEFAULT;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(8,8,64));
	RootComponent = BoxComponent;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	MeshComponent->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bCanEverTick = false;

}
void AFPickupTarget::BeginPlay()
{
	Super::BeginPlay();	
}

void AFPickupTarget::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AFPickup* PickedActor = Cast<AFPickup>(OtherActor);
	
	if (PickedActor != nullptr && PickedActor->GetPickedType() == PickedType)
		PickedActor->Drop(true);		
}
