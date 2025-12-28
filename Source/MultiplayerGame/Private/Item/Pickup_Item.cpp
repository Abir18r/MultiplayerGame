// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Pickup_Item.h"

#include "Net/UnrealNetwork.h"


// Sets default values
APickup_Item::APickup_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; // Important for multiplayer 
}

void APickup_Item::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Register Variable for Replicatiom
	DOREPLIFETIME(APickup_Item, bIsActive);
}

void APickup_Item::OnRep_ItemState_Implementation()
{
	// Called when the bIsActive changes
}

void APickup_Item::Interact_Implementation(AActor* InstigatorActor)
{
	if (HasAuthority())
	{
		bIsActive = !bIsActive;
		OnRep_ItemState();
	}
	
}


