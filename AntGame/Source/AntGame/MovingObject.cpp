// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingObject.h"

// Sets default values
AMovingObject::AMovingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MyMesh");

}

// Called when the game starts or when spawned
void AMovingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	FVector NewLocationY = GetActorLocation();
	RandomNumber = rand() % RandomNumberRange;

	//Check if object is getting to the boundary so it can move the other way
	if (NewLocation.X > WorldBoundaryPlusX) {
		DirectionX = DirectionX * -SpeedModifier;
	}

	if (NewLocation.X < WorldBoundaryMinusX) {
		DirectionX = DirectionX * -SpeedModifier;
	}

	if (NewLocation.Y > WorldBoundaryPlusY) {
		DirectionY = DirectionY * -SpeedModifier;
	}

	if (NewLocation.Y < WorldBoundaryMinusY) {
		DirectionY =DirectionY * -SpeedModifier;
	}

	if (RandomNumber >= 5) {
		NewLocation.X += DirectionX * SpeedModifier;
		SetActorLocation(NewLocation);
	}
	else {
		NewLocationY.Y += DirectionY * SpeedModifier;
		SetActorLocation(NewLocationY);
	}

}