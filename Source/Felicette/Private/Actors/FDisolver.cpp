// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FDisolver.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AFDisolver::AFDisolver()
{
	StaticMeshParameter = FName("StaticMesh");
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetAutoActivate(false);
	
	PrimaryActorTick.bCanEverTick = false;
}

void AFDisolver::BeginPlay()
{
	Super::BeginPlay();
	StartDisolve();
}

void AFDisolver::StartDisolve() const
{
	if (!SourceActor)
		return;

	UActorComponent* ActorComponent = SourceActor->GetComponentByClass(UStaticMeshComponent::StaticClass());

	if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(ActorComponent))
	{
		UNiagaraFunctionLibrary::OverrideSystemUserVariableStaticMeshComponent(NiagaraComponent,StaticMeshParameter.ToString(),StaticMesh);
		NiagaraComponent->Activate(true);		
	}
}

void AFDisolver::SetSourceActor(AActor* Source) { SourceActor = Source; }
