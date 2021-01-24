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
	PickedType = FPickedTypeEnum::Default;
	MaterialColorParameterName = FName("Color");
	MaterialSlotNameGlow = FName("Glow");

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

void AFPickup::SetPickedType(const FPickedTypeEnum PickedTypeEnum) { PickedType = PickedTypeEnum; }

FPickedTypeEnum AFPickup::GetPickedType() const { return PickedType; }

void AFPickup::SetColor(const FLinearColor Color) const
{
	if (!MeshComponent->IsMaterialSlotNameValid(MaterialSlotNameGlow))
		return;

	const int32 Index = MeshComponent->GetMaterialIndex(MaterialSlotNameGlow);
	UMaterialInstanceDynamic* MatInst = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(Index,
	                                                                                                   MeshComponent->GetMaterial(Index));
	MatInst->SetVectorParameterValue(MaterialColorParameterName, Color);
}

FLinearColor AFPickup::GetPrimaryColor() const
{
	FLinearColor Result;

	if (!MeshComponent->IsMaterialSlotNameValid(MaterialSlotNameGlow))
		return Result;

	const int32 Index = MeshComponent->GetMaterialIndex(MaterialSlotNameGlow);
	UMaterialInterface* MatInst = MeshComponent->GetMaterial(Index);

	MatInst->GetVectorParameterValue(MaterialColorParameterName, Result);

	return Result;
}

void AFPickup::Picked(AFCharacter* Other)
{
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
	                                                                  EAttachmentRule::KeepRelative,
	                                                                  EAttachmentRule::KeepRelative, true);
	AttachToComponent(Other->GetMesh(), Rules, Other->GetPickerSocketName());
}

void AFPickup::Dropped()
{
	const FDetachmentTransformRules Rules = FDetachmentTransformRules(EDetachmentRule::KeepWorld,
	                                                                  EDetachmentRule::KeepRelative,
	                                                                  EDetachmentRule::KeepRelative, true);
	DetachFromActor(Rules);
	Destroy();
}
