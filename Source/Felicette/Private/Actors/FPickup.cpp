// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickup.h"


#include "DrawDebugHelpers.h"
#include "Character/FCharacter.h"
#include "Components/FMovableComponent.h"
#include "Components/FRotatorComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AFPickup::AFPickup()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(256);
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCanEverAffectNavigation(false);
	MeshComponent->SetupAttachment(RootComponent);

	RotatorComponent = CreateDefaultSubobject<UFRotatorComponent>(TEXT("RotatorComponent"));
	MovableComponent = CreateDefaultSubobject<UFMovableComponent>(TEXT("MovableComponent"));

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AFPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AFCharacter::StaticClass()))
	{
		MovableComponent->Deactivate();
		Picked(Cast<ACharacter>(OtherActor));
	}
}

void AFPickup::Picked(ACharacter* Other)
{
	DrawDebugSphere(GetWorld(), Other->GetActorLocation(), 50, 8, FColor::Green, true, 3, 0, 3);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
	                                                                  EAttachmentRule::KeepRelative,
	                                                                  EAttachmentRule::KeepRelative, true);
	AttachToComponent(Other->GetMesh(), Rules);
}

void AFPickup::Drop()
{
	const FDetachmentTransformRules Rules = FDetachmentTransformRules(EDetachmentRule::KeepWorld,
	                                                                  EDetachmentRule::KeepRelative,
	                                                                  EDetachmentRule::KeepRelative, true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DetachFromActor(Rules);
}
