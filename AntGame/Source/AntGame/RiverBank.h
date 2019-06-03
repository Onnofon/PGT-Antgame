// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPawn.h"
#include "RiverBank.generated.h"

UCLASS()
class ANTGAME_API ARiverBank : public AActor
{
	GENERATED_BODY()
	
public:	
	ARiverBank();

protected:

public:	
	
	UFUNCTION()
		void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OffOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		AMyPawn* MyAnt;
};
