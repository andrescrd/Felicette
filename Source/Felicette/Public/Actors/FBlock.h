// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBlock.generated.h"

UCLASS()
class FELICETTE_API AFBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFBlock();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bActive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float OffsetZ;
	
	virtual void BeginPlay() override;

public:
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;	
};
