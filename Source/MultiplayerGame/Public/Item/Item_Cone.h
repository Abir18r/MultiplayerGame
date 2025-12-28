// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Cone.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AItem_Cone : public AItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem_Cone();

protected:
	// Replication Properties
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Interface Implementation
	virtual void Interact_Implementation(AActor* InstigatorActor) override;
	
	// Variable to track the state
	UPROPERTY(ReplicatedUsing = OnRep_IsEquipped)
	bool bIsEquipped;

	// Function called on Clients when bIsEquipped changes
	UFUNCTION()
	void OnRep_IsEquipped();
	
};
