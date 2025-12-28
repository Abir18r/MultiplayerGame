// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_HUD.h"


void UUI_HUD::Tick(float DeltaTime)
{
	SpeedText->SetText(FText::FromString(GetOwnerSpeed())); // Update Speed text every tick
}

FString UUI_HUD::GetOwnerSpeed()
{
	// Get the Player Pawn associated with this UI
	APawn* PlayerPawn = GetOwningPlayerPawn();

	if (!PlayerPawn) return ""; // return immediately if PlayerPawn is null
	
	// Calculate Speed (Length of the Velocity Vector)
	float CurrentSpeed = PlayerPawn->GetVelocity().Length();

	// Format as Integer
	FString SpeedString = FString::FromInt(FMath::RoundToInt(CurrentSpeed));
		
	return SpeedString;
}
