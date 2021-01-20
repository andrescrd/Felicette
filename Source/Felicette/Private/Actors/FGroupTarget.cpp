// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FGroupTarget.h"

#include "Actors/FPickup.h"
#include "Actors/FPickupTarget.h"
#include "Components/ChildActorComponent.h"


AFGroupTarget::AFGroupTarget() 
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);
	Weapon->SetChildActorClass(PickupClass);
	Weapon->CreateChildActor();
	
	PrimaryActorTick.bCanEverTick = false;
}

void AFGroupTarget::BeginPlay()
{
	Super::BeginPlay();
}

void AFGroupTarget::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GEngine->AddOnScreenDebugMessage(1,2,FColor::Green,FString::Printf(TEXT("%f - %f - %f "), Transform.GetLocation().X, Transform.GetLocation().Y, Transform.GetLocation().Z));
	
	if (PickupClass && PickupTargetClass)
	{
		FActorSpawnParameters Parameters;
		Parameters.Instigator = GetInstigator();
		Parameters.Owner = this;
		Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		
			// UChildActorComponent* PickupChild = GetWorld()->SpawnActor<UChildActorComponent>(PickupClass, GetActorLocation() +  FVector(50,50,0), FRotator(0), Parameters);
			// PickupChild->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		//
		// if (Pickup == nullptr)
		// {
		// 	UChildActorComponent* PickupChild = GetWorld()->SpawnActor<UChildActorComponent>(PickupClass, GetActorLocation() +  FVector(50,50,0), FRotator(0), Parameters);
		// 	PickupChild->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		//
		//
		// 	
		// 	
		// }
		//
		// if (Target == nullptr)
		// {
		// 	Target = GetWorld()->SpawnActor<AFPickupTarget>(PickupTargetClass, GetActorLocation() + FVector(-50,-50,0), FRotator(0), Parameters);
		// 	Target->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		// 	Target->SetActorLabel("__Target");
		// }
	}
}

void AFGroupTarget::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	
}

void AFGroupTarget::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

void AFGroupTarget::PostInitProperties()
{
	Super::PostInitProperties();
}