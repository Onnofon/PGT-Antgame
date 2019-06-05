// Fill out your copyright notice in the Description page of Project Settings.

#include "RainPuddle.h"
#include "WeatherCycle.h"


float speed;
//FVector RainPuddleLocation;
//FVector newRainPuddleLocation;

ARainPuddle::ARainPuddle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARainPuddle::BeginPlay()
{
	Super::BeginPlay();
	RainPuddleLocation = GetActorLocation();
	newRainPuddleLocation = RainPuddleLocation;
	SetActorLocation(RainPuddleLocation);
	speed = 4.0f;
}

// Called every frame
void ARainPuddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Global::Raining == false) 
	{
		//hide object
		newRainPuddleLocation.Z -= speed * DeltaTime;
		SetActorLocation(newRainPuddleLocation);
	}
	if (newRainPuddleLocation.Z < RainPuddleLocation.Z - 20) 
	{
		DisableActor();
		SetActorLocation(newRainPuddleLocation);
	}

	if (Global::Raining == true)
	{
		EnableActor();

		if (newRainPuddleLocation.Z != RainPuddleLocation.Z) {

			newRainPuddleLocation.Z += speed * DeltaTime;
			SetActorLocation(newRainPuddleLocation);
		}
		if (newRainPuddleLocation.Z >= RainPuddleLocation.Z) {
			SetActorLocation(RainPuddleLocation);
		}
	}
}

void ARainPuddle::DisableActor()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}
void ARainPuddle::EnableActor() 
{

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

