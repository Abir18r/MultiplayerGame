// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"

#include "Net/UnrealNetwork.h"


// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; // Important for multiplayer 
	
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObjectMesh");
	ObjectMesh->SetupAttachment(RootComponent);
}

void AItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Register Variable for Replicatiom
	DOREPLIFETIME(AItemBase, bIsActive);
}

void AItemBase::OnRep_ItemState_Implementation()
{
	// Called when the bIsActive changes
}

void AItemBase::Interact_Implementation(AActor* InstigatorActor)
{
	if (HasAuthority())
	{
		bIsActive = !bIsActive;
		OnRep_ItemState();
	}
}


