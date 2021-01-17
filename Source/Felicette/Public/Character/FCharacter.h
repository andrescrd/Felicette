// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FCharacter.generated.h"

UCLASS(Blueprintable)
class AFCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFCharacter();

protected:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	// class UCameraComponent* TopDownCameraComponent;
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	// class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName PickerSocketName;

public:
	virtual void Tick(float DeltaSeconds) override;
	FName GetPickerSocketName() const;	
	bool IsMoving() const;
	void SetNewMoveDestination(FVector DestLocation, bool KeepAxisZValue) const;
};

