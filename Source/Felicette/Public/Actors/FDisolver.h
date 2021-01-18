// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NiagaraComponentPool.h"
#include "GameFramework/Actor.h"
#include "FDisolver.generated.h"

UCLASS()
class FELICETTE_API AFDisolver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDisolver();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UNiagaraComponent* NiagaraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* SourceActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StaticMeshParameter;
	
	virtual void BeginPlay() override;
	void StartDisolve() const;

	UFUNCTION()
	void HandleOnSystemFinished(class UNiagaraComponent* PSystem);
	
public:
	void SetSourceActor(class AActor* Source);

};
