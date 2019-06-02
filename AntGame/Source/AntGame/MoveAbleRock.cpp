// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveAbleRock.h"
#include <Runtime/Engine/Classes/Components/StaticMeshComponent.h>
// Sets default values
AMoveAbleRock::AMoveAbleRock()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMoveAbleRock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveAbleRock::Tick(float DeltaTime)
{
	//SFName rock;
	Super::Tick(DeltaTime);
	//Mesh->SetSimulatePhysics(true);
	//Mesh->SetMassOverrideInKg(rock, weight, true);
}
