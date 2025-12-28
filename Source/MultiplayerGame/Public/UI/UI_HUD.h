// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UI_HUD.generated.h"

UCLASS()
class MULTIPLAYERGAME_API UUI_HUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void Tick( float DeltaTime );
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> SpeedText;
	
	UFUNCTION( BlueprintCallable )
	FString GetOwnerSpeed();
};
