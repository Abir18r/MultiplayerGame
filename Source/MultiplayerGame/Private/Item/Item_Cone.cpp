// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item_Cone.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AItem_Cone::AItem_Cone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AItem_Cone::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AItem_Cone, bIsEquipped);
}

void AItem_Cone::Interact_Implementation(AActor* InstigatorActor)
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
		ACharacter* PlayerCharacter = Cast<ACharacter>(InstigatorActor);

		if (PlayerCharacter)
		{
			// Update State
			bIsEquipped = true;
            
			// Call on Server
			OnRep_IsEquipped();

			// Attach to the character (S_Hat) socket
			this->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("S_Hat"));
		}
	}
}

void AItem_Cone::OnRep_IsEquipped()
{
	if (bIsEquipped)
	{
		// runs on the Client too
		SetActorEnableCollision(false);
	}
}
