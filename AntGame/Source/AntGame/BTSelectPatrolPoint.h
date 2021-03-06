/// <summary>
/// Custom node for the behavior tree of the Beetle for following the waypoints from an array(BeetleAiController) \n Inherits from UBBTaskNode because then it shows up in behavior tree
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSelectPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class ANTGAME_API UBTSelectPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
