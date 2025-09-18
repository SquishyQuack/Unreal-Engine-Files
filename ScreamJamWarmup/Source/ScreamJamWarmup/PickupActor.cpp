// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "InventoryActor.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(150.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("Trigger"));

	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(SphereMesh.Object);
		MeshComponent->SetRelativeScale3D(FVector(0.5f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Engine/BasicShapes/BasicShapeMaterial"));

	if (Material.Succeeded())
	{
		MeshComponent->SetMaterial(0, Material.Object);
	}

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnOverlapBegin);

	if (mItemName.IsEmpty())
	{
		mItemName = TEXT("Default item");
	}
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupActor::Show(bool visible)
{
	ECollisionEnabled::Type collision = visible ?
		ECollisionEnabled::QueryAndPhysics :
		ECollisionEnabled::NoCollision;

	this->SetActorTickEnabled(visible);

	this->MeshComponent->SetVisibility(visible);
	this->MeshComponent->SetCollisionEnabled(collision);

	this->CollisionComponent->SetCollisionEnabled(collision);
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::OnInteract()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	if (PlayerCharacter)
	{
	
		FString pickup = FString::Printf(TEXT("Picked up: %s"), *mItemName);
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::White, pickup);

		AddToPlayerInventoryBP(this);

		UE_LOG(LogTemp, Warning, TEXT("Item Picked out"));
	}

	Show(false);
}

FString APickupActor::GetItemName() const
{
	return mItemName;
}

void APickupActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision with Pickup Item"));
		OnInteract();
	}
}

