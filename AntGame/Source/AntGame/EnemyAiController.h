// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAiController.generated.h"

/**
 * 
 */
UCLASS()
class ANTGAME_API AEnemyAiController : public AAIController
{
	GENERATED_BODY()

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
