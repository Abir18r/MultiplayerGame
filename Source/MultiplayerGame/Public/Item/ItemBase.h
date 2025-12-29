// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class USphereComponent;
class UWidgetComponent;

UCLASS()
class MULTIPLAYERGAME_API AItemBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();
	void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (ExposeOnSpawn = true))
	UStaticMeshComponent* ObjectMesh;
	
	protected:
	// Replication Properties
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(ReplicatedUsing = OnRep_ItemState)
	bool bIsActive;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRep_ItemState();
	
	// Interface Implementation
	virtual void Interact_Implementation(AActor* InstigatorActor) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* OverlapSphere;

	// The Widget (The "Press E" Popup)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* InteractionWidget;

	// Overlap Events
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void CheckLooking();

private:
	FTimerHandle TimerHandle_LookAtCheck;

	// The player currently inside the sphere
	UPROPERTY()
	APawn* OverlappingPawn;
};