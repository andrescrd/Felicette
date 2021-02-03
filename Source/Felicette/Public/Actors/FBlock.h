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
	FVector StartLocation;
	FVector EndLocation;
	bool bIsHighlighted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadOnly)
	class UMaterialInterface* MaterialPrimary;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UMaterialInterface* MaterialSecondary;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UMaterialInterface* MaterialHeiglight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)	
	FName MaterilaSlotName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)	
	FName MaterilaSlotNameGlow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
	class UTimelineComponent* TimelineComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UCurveFloat* Curve;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
	bool bActive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	float OffsetZ;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	float TimelineTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class USoundBase* ActiveSound;
	
	virtual void BeginPlay() override;
	void SetupTimeline();

	UFUNCTION()
	void OnTimelineHandler(const float Output);

public:
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;

	bool HasItemOverlapped() const;
	bool IsValid();
	bool IsActive() const;
};
