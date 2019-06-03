// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPickUp.h"
#include "Classes/Components/ShapeComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values
AMyPickUp::AMyPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	// PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	// RootComponent = PickupRoot;

	// PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	// PickupMesh->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); //no scale
	
	// PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	// PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	//PickupBox->bGenerateOverlapEvents = true;
	// PickupBox->OnComponentBeginOverlap.AddDynamic(this, &AMyPickUp::OnPlayerEnterPickupBox);
	// PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void AMyPickUp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPickUp::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//temp destroy pickup
	Destroy();
	//add points to total score, 
	//move object above player (attach it some way?)
}

