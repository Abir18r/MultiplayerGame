// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Cube.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AItem_Cube : public AItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem_Cube();

protected:
	
	// Interface Implementation
	virtual void Interact_Implementation(AActor* InstigatorActor) override;
};
