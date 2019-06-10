/// <summary>
/// Old starting point for enemy AI current not used
/// </summary>

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
