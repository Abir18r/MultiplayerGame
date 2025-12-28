// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "Pickup_Item.generated.h"

UCLASS()
class MULTIPLAYERGAME_API APickup_Item : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup_Item();
	
	protected:
	// Replication Properties
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(ReplicatedUsing = OnRep_ItemState)
	bool bIsActive;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRep_ItemState();
	
	// Interface Implementation
	virtual void Interact_Implementation(AActor* InstigatorActor) override;
};
