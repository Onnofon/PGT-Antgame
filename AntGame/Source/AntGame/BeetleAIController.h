// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BeetleAIController.generated.h"

/**
 * 
 */
UCLASS()
class ANTGAME_API ABeetleAIController : public AAIController
{
	GENERATED_BODY()

		//Blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName LocationToGoKey;
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName PlayerKey;

	/*
	Array for the waypoints for the pathfinding
	Stored as an AActor so I can use the GetAllActorsOfClass funtion
	*/
	TArray<AActor*> PatrolPoints;
	/*
	Reference to the behavior tree component
	Used only to kickstart the tree from the possess function
	BeetleAI holds the behaviortree reference for the logic
	Needs to be serperate because controller inherits aicontroller and cannot be used as a moving object in the world
	*/
	class UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;

	virtual void Possess(APawn* Pawn) override;

	

public:
	ABeetleAIController();

	//Function that gets called when player is in sight
	void SetPlayerCaught(APawn* Pawn);

	//Used to get currentpatrolpoint for blackboard BTSelectPatrolPoint 
	int32 CurrentPatrolPoint = 0;
	//Function to get all patrol points and blackcomponent for use in BTSelectPatrolPoint class
	FORCEINLINE UBlackboardComponent* GetBlackBoardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

};