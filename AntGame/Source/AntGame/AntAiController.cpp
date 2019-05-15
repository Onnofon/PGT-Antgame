// Fill out your copyright notice in the Description page of Project Settings.
#define printf(text, fstring)  if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "AntAiController.h"
#include "AntAI.h"
#include "AntPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyPawn.h"

AAntAiController::AAntAiController()
{
	//Initialize Blackboard behavior tree
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	//Initialize Keys
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";
	CurrentPatrolPoint = 0;
}

//Function to posses the AantAI character and make it follow the behavior tree logic
void AAntAiController::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	AAntAI* AICharacter = Cast<AAntAI>(Pawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			//Intialize the blackboard for the ant
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
		//Get all the Target Points
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAntPatrolPoint::StaticClass(), PatrolPoints);

		//Start the behavior tree
		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}
}

// Called when ant is commanded to leave the player from AntAI class
void AAntAiController::CommandLeavePlayer(APawn * Pawn)
{
	AMyPawn* Player = Cast<AMyPawn>(Pawn);
	if (BlackboardComp)
	{
		//Set the playerkey in the blackboard to NULL If PlayerKey is NULL behavior tree goes back to waypoint following
		BlackboardComp->SetValueAsObject(PlayerKey, NULL);
		//Decrement numberFollowingAnts for interaction with obstacles in game
		Player->numberFollowingAnts--;
	}
}


//Called when ant is commanded to follow from AntAI
void AAntAiController::SetPlayerFollow(APawn * Pawn)
{
	AMyPawn* Player = Cast<AMyPawn>(Pawn);
	if (BlackboardComp)
	{
		// Set the playerkey in the blackboard to player location If PlayerKey is not NULL behavior tree goes into a loop following the player
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
		// Increment numberFollowingAnts for interaction with obstacles in game
		Player->numberFollowingAnts++;
	}
}

