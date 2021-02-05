// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FTeleport.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/FCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/GameModes/FGameMode.h"

// Sets default values
AFTeleport::AFTeleport()
{
	bIsActivated = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCOmponent"));
	BoxComponent->SetBoxExtent(FVector(8, 8, 32));
	RootComponent = BoxComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Overlap);
	MeshComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = false;
}

void AFTeleport::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AFCharacter::StaticClass()) && bIsActivated)
	{
		OnCharacterEnter(Cast<AFCharacter>(OtherActor));

		AFGameMode* GM = GetWorld()->GetAuthGameMode<AFGameMode>();
		GM->SetPlayerOnTeleport();

		if(PickedSound)
			UGameplayStatics::PlaySound2D(this, PickedSound);
	}
}

void AFTeleport::SetIsActivated(const bool IsActivated) { bIsActivated = IsActivated; }
