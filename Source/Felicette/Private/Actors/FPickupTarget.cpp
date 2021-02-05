// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickupTarget.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/GameModes/FGameMode.h"

// Sets default values
AFPickupTarget::AFPickupTarget()
{
	PickedType = FPickedTypeEnum::Default;
	MaterialColorParameterName = FName("Color");
	MaterialSlotName = FName("Base");
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(8, 8, 64));
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Overlap);
	MeshComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = false;
}

void AFPickupTarget::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AFPickup* PickedActor = Cast<AFPickup>(OtherActor);

	if (PickedActor != nullptr && PickedActor->GetPickedType() == PickedType)
	{		
		OnPickedCollected(PickedActor);

		AFGameMode* Gm = GetWorld()->GetAuthGameMode<AFGameMode>();
		Gm->AddPickedCollected(1);
		PickedActor->Dropped();
		
		if(PickedSound)
			UGameplayStatics::PlaySound2D(this, PickedSound);
	}
}

void AFPickupTarget::SetPickedType(const FPickedTypeEnum PickedTypeEnum) { PickedType = PickedTypeEnum; }

void AFPickupTarget::SetColor(const FLinearColor Color) const
{			
	if(!MeshComponent->IsMaterialSlotNameValid(MaterialSlotName))
		return;
	
	const int32 Index = MeshComponent->GetMaterialIndex(MaterialSlotName);	
	UMaterialInstanceDynamic* MatInst = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(Index,
        MeshComponent->GetMaterial(Index));	                                                                                                  
	MatInst->SetVectorParameterValue(MaterialColorParameterName, Color);
}

FPickedTypeEnum AFPickupTarget::GetPickedType() const { return PickedType; }
