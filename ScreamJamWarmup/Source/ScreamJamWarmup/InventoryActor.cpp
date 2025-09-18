// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActor.h"

// Sets default values
AInventoryActor::AInventoryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("Inventory Initialized"));
}

// Called when the game starts or when spawned
void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventoryActor::AddToInventory(APickupActor* actor)
{
	if (actor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item is null"));

	}
	mInventory.Add(actor);
	UE_LOG(LogTemp, Warning, TEXT("Item add to inv"));
}

void AInventoryActor::PrintInventory()
{
	FString sInventory = "";

	for (APickupActor* item : mInventory)
	{
		if (item)
		{
			sInventory.Append(item->GetItemName());
			sInventory.Append(" | ");
			UE_LOG(LogTemp, Warning, TEXT("Inventory Item: %s"), *item->GetName());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Inventory contains a NULL item!"));
		}

		GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, *sInventory);
	}

}

