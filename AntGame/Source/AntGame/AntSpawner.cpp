// Fill out your copyright notice in the Description page of Project Settings.
#define printf(text, fstring)  if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Green, FString::Printf(TEXT(text), fstring))
#include "AntSpawner.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

/**
 * @brief 
 * Sets default values
 */
AAntSpawner::AAntSpawner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAntSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}
/**
 * @brief 
 * Called every frame
 */ 
void AAntSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//So long as max number of ants has not been reached decrement delay when delay has reached 0 Spawn the next ant
	if (currentAnts <= maxAnts)
	{
		delay--;
		if(delay <= 0 )
		Spawn();
	}
}
/**
 * @brief 
 * Spawning ants and resetting timer for the next spawn
 */
void AAntSpawner::Spawn()
{
	//Set a new delay time min and max time can be set in editor
	delay = FMath::FRandRange(minTimeDelay, maxTimeDelay);
	//If there is a reference to the antAI
	if (ToSpawn)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			//Set the variables for the spawnactor function
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			FVector NewLocation = GetActorLocation() + FVector(150.f, 0.f, 0.f);

			//Spawn ant in the world
			world->SpawnActor<AAntAI>(ToSpawn, NewLocation, FRotator::ZeroRotator, spawnParams);
			//Ant spawned increment currentAnt number
			currentAnts++;
		}
	}
}

// Called to bind functionality to input
void AAntSpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

