// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.h"
#include "InventoryActor.generated.h"

UCLASS()
class SCREAMJAMWARMUP_API AInventoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable)
	void AddToInventory(APickupActor* actor);

	UFUNCTION(BlueprintCallable)
	void PrintInventory();


private:
	TArray<APickupActor*> mInventory;

};
