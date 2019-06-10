// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSelectPatrolPoint.h"
#include "BeetlePatrolPoint.h"
#include "BeetleAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

/**
 * @brief 
 * Function used for setting next waypoint
 */
EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABeetleAIController* AICon = Cast<ABeetleAIController>(OwnerComp.GetAIOwner());

	/*If the Controller is valid:
	1)Get the Blackboard Component and the Current Point of the ant
	2)Search for the next point, which will be different from the Current Point
	*/
	if (AICon) 
	{
		//Get blackboard currentpoint and all patrol points
		UBlackboardComponent* BlackboardComp = AICon->GetBlackBoardComp();
		ABeetlePatrolPoint* CurrentPoint = Cast<ABeetlePatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

		//Store next patrol point
		ABeetlePatrolPoint* NextPatrolPoint = nullptr;

		//If the AI has not reached the end set to next point in array else start from beginning of array
		if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() -1)
		{
			NextPatrolPoint = Cast<ABeetlePatrolPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]);
		}
		else
		{
			NextPatrolPoint = Cast<ABeetlePatrolPoint>(AvailablePatrolPoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}
		//Set the value of the blackboard key to the next waypoint location
		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
