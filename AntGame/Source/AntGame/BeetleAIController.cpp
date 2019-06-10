// Fill out your copyright notice in the Description page of Project Settings.

#include "BeetleAIController.h"
#include "BeetleAI.h"
#include "BeetlePatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/**
 * @brief 
 * Setting the blackboard en behavior tree and keys
 */
ABeetleAIController::ABeetleAIController()
{
	//Initialize Blackboard behavior tree
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	//Initialize Keys
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";
	CurrentPatrolPoint = 0;
}
/**
 * @brief 
 * Function to posses the BeetleAI character and make it follow the behavior tree logic
 */
void ABeetleAIController::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	ABeetleAI* AICharacter = Cast<ABeetleAI>(Pawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			//Intialize the blackboard for the beetle
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
		//Get all targetpoints in the world
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABeetlePatrolPoint::StaticClass(), PatrolPoints);

		//Start the behavior tree
		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}
}

/**
 * @brief 
 * Function called when player was in sight of the beetle's vision
 */
void ABeetleAIController::SetPlayerCaught(APawn * Pawn)
{
	if (BlackboardComp)
	{
		//Set keyvalue to the location of the player so it can chase
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}
}


