// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAiController.h"
#include "EnemyAi.h"

void AEnemyAiController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	AEnemyAi* EnemyAi = Cast<AEnemyAi>(GetPawn());

	if (EnemyAi) 
	{
		EnemyAi->MoveToWaypoint();
	}
}
