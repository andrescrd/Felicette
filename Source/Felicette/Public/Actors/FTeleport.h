// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Character/FCharacter.h"
#include "GameFramework/Actor.h"
#include "FTeleport.generated.h"

UCLASS()
class FELICETTE_API AFTeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFTeleport();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsActivated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class USoundBase* PickedSound;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void SetIsActivated(bool IsActivated);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterEnter(AFCharacter* Character);
	
};
