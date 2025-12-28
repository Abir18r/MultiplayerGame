// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item_Cone.h"

#include "GameFramework/Character.h"


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
}

void AItem_Cone::Interact_Implementation(AActor* InstigatorActor)
{
	if (HasAuthority())
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(InstigatorActor);

		if (PlayerCharacter)
		{
			// DISABLE COLLISION
			SetActorEnableCollision(false);
            
			this->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Head")
			);
		}
	}
}
