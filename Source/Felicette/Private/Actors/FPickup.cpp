// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickup.h"
#include "DrawDebugHelpers.h"
#include "Character/FCharacter.h"
#include "Components/FMovableComponent.h"
#include "Components/FRotatorComponent.h"
#include "Components/SphereComponent.h"
#include "Actors/FDisolver.h"

// Sets default values
AFPickup::AFPickup()
{
	PickedType = FPickedTypeEnum::DEFAULT;

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
	if (AFCharacter* Character = Cast<AFCharacter>(OtherActor))
	{
		MovableComponent->Deactivate();
		Picked(Character);
	}
}

FPickedTypeEnum AFPickup::GetPickedType() const { return PickedType; }

void AFPickup::Picked(AFCharacter* Other)
{
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
	                                                                  EAttachmentRule::KeepRelative,
	                                                                  EAttachmentRule::KeepRelative, true);
	AttachToComponent(Other->GetMesh(), Rules, Other->GetPickerSocketName());
}

void AFPickup::Drop(const bool SpawnEmmiter)
{
	const FDetachmentTransformRules Rules = FDetachmentTransformRules(EDetachmentRule::KeepWorld,
	                                                                  EDetachmentRule::KeepRelative,
	                                                                  EDetachmentRule::KeepRelative, true);
	DetachFromActor(Rules);

	if(SpawnEmmiter && DisolverClass)
	{	
		AFDisolver* Dissolved = GetWorld()->SpawnActorDeferred<AFDisolver>(DisolverClass,MeshComponent->GetComponentTransform(),this, GetInstigator());
			
		Dissolved->SetSourceActor(this);
		Dissolved->FinishSpawning(MeshComponent->GetComponentTransform(),true);
	}

	Destroy();
}
