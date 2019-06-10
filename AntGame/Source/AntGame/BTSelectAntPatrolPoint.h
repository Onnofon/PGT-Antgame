/// <summary>
/// Custom node for the behavior tree of the Ant for following the waypoints from an array(AntAiController)
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSelectAntPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class ANTGAME_API UBTSelectAntPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
