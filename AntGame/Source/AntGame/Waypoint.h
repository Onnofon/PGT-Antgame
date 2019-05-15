// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Waypoint.generated.h"

/**
 * 
 */
UCLASS()
class ANTGAME_API AWaypoint : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	int GetWaypointOrder();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcces = "true"))
	int WaypointOrder;
	
};
