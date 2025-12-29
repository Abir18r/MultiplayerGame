// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; // Important for multiplayer 
	
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObjectMesh");
	RootComponent = ObjectMesh;
	
	OverlapSphere = CreateDefaultSubobject<USphereComponent>("OverlapSphere");
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetSphereRadius(150.0f); // The "Overlap Area" size
	// Only query pawns, ignore physics objects
	OverlapSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Setup Widget
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>("InteractionWidget");
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen); // Makes it always face camera
	InteractionWidget->SetDrawAtDesiredSize(true);
	InteractionWidget->SetVisibility(false);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind Overlap Events
	if (HasAuthority() == false || IsRunningDedicatedServer() == false) // local player
	{
		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnSphereOverlap);
		OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnSphereEndOverlap);
	}
}

void AItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Register Variable for Replicatiom
	DOREPLIFETIME(AItemBase, bIsActive);
}

void AItemBase::OnRep_ItemState_Implementation()
{
	// Called when the bIsActive changes
}

void AItemBase::Interact_Implementation(AActor* InstigatorActor)
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
		bIsActive = !bIsActive;
		OnRep_ItemState();
	}
}

void AItemBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (PlayerPawn && PlayerPawn->IsLocallyControlled())
	{
		OverlappingPawn = PlayerPawn;

		// Start checking 10 times per second
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_LookAtCheck, this, &AItemBase::CheckLooking, 0.1f, true);
	}
}

void AItemBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (PlayerPawn && PlayerPawn->IsLocallyControlled())
	{
		OverlappingPawn = nullptr;
		// Stop Checking
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_LookAtCheck);
		// Hide Widget
		InteractionWidget->SetVisibility(false);
	}
}

void AItemBase::CheckLooking()
{
	if (!OverlappingPawn) return;

	FVector Start;
	FRotator CamRot;
	OverlappingPawn->GetController()->GetPlayerViewPoint(Start, CamRot);

	// Trace distance same as Interact
	FVector End = Start + (CamRot.Vector() * 500.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OverlappingPawn); // Ignore the player

	float TraceRadius = 30.0f;
	float TraceHalfHeight = 30.0f; 
	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(TraceRadius, TraceHalfHeight);

	//  Perform Trace
	bool bHit = GetWorld()->SweepSingleByChannel(
	   HitResult, 
	   Start, 
	   End, 
	   FQuat::Identity, 
	   ECC_Visibility, 
	   CapsuleShape, 
	   Params
	);

	bool bIsLookingAtItem = (bHit && HitResult.GetActor() == this);

	// Toggle Widget Visibility
	if (InteractionWidget->IsVisible() != bIsLookingAtItem)
	{
		InteractionWidget->SetVisibility(bIsLookingAtItem);
	}
}