// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherCycle.generated.h"

class UMaterialInstanceDynamic;

UCLASS()
class ANTGAME_API AWeatherCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeatherCycle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Sun();
	virtual void Rain();

	virtual void NextStage();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weather)
		class UParticleSystemComponent* RainParticles;

private:
	UMaterialInstanceDynamic* DynamicMaterial;


	// This is a declaration of your variable, which tells the linker this value
	// is found elsewhere.  Anyone who wishes to use it must include global.h,
	// either directly or indirectly.
	
};
