// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/FPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Actors/FBlock.h"
#include "Character/FCharacter.h"
#include "Engine/World.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

AFPlayerController::AFPlayerController()
{
	DistanceToMove = 120;
}

void AFPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* CurrentActor = UGameplayStatics::GetActorOfClass(GetWorld(), AFCharacter::StaticClass()))
		MyCharacter = Cast<AFCharacter>(CurrentActor);
}

void AFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AFPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPlayerController::MoveRight);
}

void AFPlayerController::SetNewMoveDestination(const FVector DestLocation) const
{
	if (MyCharacter)
		MyCharacter->SetNewMoveDestination(DestLocation, true);
}

void AFPlayerController::MoveForward(float Value)
{
	if (MyCharacter && Value != 0)
	{
		FVector StartLocation = MyCharacter->GetActorLocation();
		StartLocation.X += DistanceToMove * Value;
		DoMovement(StartLocation);
	}
}

void AFPlayerController::MoveRight(float Value)
{
	if(MyCharacter && Value!=0)
	{
		FVector StartLocation = MyCharacter->GetActorLocation();
		StartLocation.Y += DistanceToMove * Value;
		DoMovement(StartLocation);
	}
}

void AFPlayerController::DoMovement(FVector StartLocation) const
{
	StartLocation.Z += 100;

	FVector EndLocation = StartLocation;
	EndLocation.Z -= 200;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic);

	if (HitResult.Actor != nullptr && HitResult.Actor->IsA(AFBlock::StaticClass()))
		SetNewMoveDestination(HitResult.Actor->GetActorLocation());
}

void AFPlayerController::ToggleInput(const bool Enable)
{
	if (Enable)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
}
