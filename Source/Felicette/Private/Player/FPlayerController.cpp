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
	DistanceToMove = 220;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("SetDestination", EInputEvent::IE_Pressed, this, &AFPlayerController::OnDestination);
}

void AFPlayerController::SetNewMoveDestination(const FVector DestLocation) { GetCurrentCahracter()->SetNewMoveDestination(DestLocation, true); }

// ReSharper disable once CppMemberFunctionMayBeConst
void AFPlayerController::OnDestination()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult);	
	
	if (HitResult.GetActor() != nullptr &&
		HitResult.GetActor()->IsA(AFBlock::StaticClass()))
	{
		AFBlock* Block = Cast<AFBlock>(HitResult.GetActor());

		if(!Block->IsValid() || (Block->HasItemOverlapped() && GetCurrentCahracter()->HasItemPicked()))
			return;;

		FVector BlockLocation = Block->GetActorLocation();
		const FVector CharacterLocation = GetCurrentCahracter()->GetActorLocation();

		BlockLocation.Z = CharacterLocation.Z;		
		const float Distance = (BlockLocation - CharacterLocation).Size();

		// DrawDebugLine(GetWorld(),CharacterLocation, BlockLocation,FColor::Green, true,3,0,5);			
		GEngine->AddOnScreenDebugMessage(1,2,FColor::Green,FString::Printf(TEXT("Distance is %f and max is  %f" ),Distance,DistanceToMove));
		
		if(Distance > DistanceToMove)
			return;
		
		if(Block->IsActive())
			SetNewMoveDestination(HitResult.GetActor()->GetActorLocation());
	}
}

AFCharacter* AFPlayerController::GetCurrentCahracter()
{
	if(!IsValid(MyCharacter))
	{
		if (AActor* CurrentActor = UGameplayStatics::GetActorOfClass(GetWorld(), AFCharacter::StaticClass()))
			MyCharacter = Cast<AFCharacter>(CurrentActor);
	}

	return MyCharacter;	
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
