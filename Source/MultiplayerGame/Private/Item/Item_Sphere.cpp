// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item_Sphere.h"

#include "Net/UnrealNetwork.h"


// Sets default values
AItem_Sphere::AItem_Sphere()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	ObjectMesh->SetSimulatePhysics(true); // Enable Physics for the Mesh
}

void AItem_Sphere::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Register the variable for replication
	DOREPLIFETIME(AItem_Sphere, SphereColor);
}

void AItem_Sphere::OnRep_SphereColor()
{
	if (ObjectMesh)
	{
		// Create a Dynamic Material Instance
		UMaterialInstanceDynamic* DMI = ObjectMesh->CreateAndSetMaterialInstanceDynamic(0);
		
		if (DMI)
		{
			// "BaseColor" must match the Parameter Name in Material Editor
			DMI->SetVectorParameterValue(FName("BaseColor"), SphereColor);
		}
	}
}

void AItem_Sphere::Interact_Implementation(AActor* InstigatorActor)
{
	if (HasAuthority())
	{
		// Generate a random color
		SphereColor = FLinearColor::MakeRandomColor();

		// RepNotify functions are NOT automatically called on the Server.
		// call it manually so the Host sees the change too.
		OnRep_SphereColor();
	}
}


