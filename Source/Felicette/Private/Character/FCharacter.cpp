// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/FCharacter.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AFCharacter::AFCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(56.0f, 56.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AFCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

FName AFCharacter::GetPickerSocketName() const { return PickerSocketName; }

bool AFCharacter::IsMoving() const { return GetVelocity().Size() > 0; }

void AFCharacter::SetNewMoveDestination(FVector DestLocation, const bool KeepAxisZValue) const
{
	if(IsMoving())
		return;
	
	float const Distance = FVector::Dist(DestLocation, GetActorLocation());
	
	if(KeepAxisZValue)
	{
		const float Radius = GetCapsuleComponent()->GetScaledCapsuleRadius();
		float NewZ= GetActorLocation().Z;
		NewZ -= Radius;
		DestLocation.Z = NewZ;
	}
	
	// DrawDebugSphere(GetWorld(), DestLocation, 50, 8, FColor::Red, true, 3, 0, 3);

	if (AAIController* AI = Cast<AAIController>(GetController()))
		AI->MoveToLocation(DestLocation, 5, false, false);
}
