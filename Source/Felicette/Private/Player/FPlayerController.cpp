// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/FPlayerController.h"


#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
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
		MyPawn = Cast<APawn>(CurrentActor);
}

void AFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AFPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPlayerController::MoveRight);
}

void AFPlayerController::SetNewMoveDestination(const FVector DestLocation) const
{
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
		DrawDebugSphere(GetWorld(), DestLocation, 50, 8, FColor::Red, true, 3, 0, 3);
			
		if(AAIController* AI = Cast<AAIController>(MyPawn->GetController()))
			AI->MoveToLocation(DestLocation,0,false);	
	}
}

void AFPlayerController::MoveForward(float Value)
{
	if (MyPawn)
	{
		FVector StartLocation = MyPawn->GetActorLocation();
		StartLocation.X += DistanceToMove * Value;
		StartLocation.Z += 100;

		FVector EndLocation = StartLocation;
		EndLocation.Z -= 300;

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic);

		if (HitResult.Actor != nullptr && HitResult.Actor->IsA(AFBlock::StaticClass()))
			SetNewMoveDestination(HitResult.Actor->GetActorLocation());
	}
}

void AFPlayerController::MoveRight(float Value)
{
	if (MyPawn)
	{
		FVector StartLocation = MyPawn->GetActorLocation();
		StartLocation.Y += DistanceToMove * Value;
		StartLocation.Z += 100;

		FVector EndLocation = StartLocation;
		EndLocation.Z -= 300;

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic);

		if (HitResult.Actor != nullptr && HitResult.Actor->IsA(AFBlock::StaticClass()))
			SetNewMoveDestination(HitResult.Actor->GetActorLocation());
	}
}

