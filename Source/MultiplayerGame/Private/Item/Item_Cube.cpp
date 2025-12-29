// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item_Cube.h"

#include "Components/SphereComponent.h"


// Sets default values
AItem_Cube::AItem_Cube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AItem_Cube::Interact_Implementation(AActor* InstigatorActor)
{
	if (OverlapSphere)
	{
		// If the player actually overlapping the sphere then it can interact otherwise NOT
		if (!OverlapSphere->IsOverlappingActor(InstigatorActor))
		{
			return; 
		}
	}
	
	if (HasAuthority())
	{
		Destroy();
	}
}
