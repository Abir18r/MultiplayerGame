// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Sphere.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AItem_Sphere : public AItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem_Sphere();

protected:
	// Replication Properties
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(ReplicatedUsing = OnRep_SphereColor)
	FLinearColor SphereColor;
	
	UFUNCTION()
	void OnRep_SphereColor();
	
	// Interface Implementation
	virtual void Interact_Implementation(AActor* InstigatorActor) override;
};
