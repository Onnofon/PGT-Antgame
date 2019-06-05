// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RainPuddle.generated.h"

UCLASS()
class ANTGAME_API ARainPuddle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARainPuddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Disable")
		bool Fading;
		FVector RainPuddleLocation;
		FVector newRainPuddleLocation;

	UFUNCTION(BlueprintCallable, Category = "Disable")
		void DisableActor();
	UFUNCTION(BlueprintCallable, Category = "Enable")
		void EnableActor();
};