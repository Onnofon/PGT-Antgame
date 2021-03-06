// Fill out your copyright notice in the Description page of Project Settings.

#include "WeatherCycle.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"

int delay;
int NextCycle;
bool Global::Raining;

// Sets default values
AWeatherCycle::AWeatherCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RainParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));

}

// Called when the game starts or when spawned
void AWeatherCycle::BeginPlay()
{
	Super::BeginPlay();

	auto Cube = FindComponentByClass<UStaticMeshComponent>();
	
	auto Material = Cube->GetMaterial(0);

	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Cube->SetMaterial(0, DynamicMaterial);
	
	Sun();
}


void AWeatherCycle::Sun() {
	DynamicMaterial->SetScalarParameterValue(TEXT("CurrentStage"), 1);
	delay = FMath::FRandRange(minTime, maxTime);
	RainParticles->SetVisibility(false);
	Global::Raining = false;

}

void AWeatherCycle::Rain() {
	DynamicMaterial->SetScalarParameterValue(TEXT("CurrentStage"), 0);
	delay = FMath::FRandRange(minTime, maxTime);
	RainParticles->SetVisibility(true);
	Global::Raining = true;
}

void AWeatherCycle::NextStage() {
	NextCycle = FMath::FRandRange(0, 2);

	if (NextCycle == 0) {
		Sun();
	}
	else if (NextCycle == 1) {
		Rain();
	}
}

// Called every frame
void AWeatherCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    delay = delay - 1;

	if (delay <= 0) {
		NextStage();
	}
}

