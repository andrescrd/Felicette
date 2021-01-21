// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPlayerController.generated.h"

UCLASS()
class AFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AFCharacter* MyCharacter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DistanceToMove;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void SetNewMoveDestination(const FVector DestLocation) const;
	void OnDestination();

public:
	void ToggleInput(bool Enable);
};
