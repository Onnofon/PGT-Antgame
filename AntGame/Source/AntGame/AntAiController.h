/// <summary>
/// Brain class for the Ant AI communicates with the behavior tree \n Inherits from AIController for Possessing and easier Behavior tree support
/// </summary>
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AntAiController.generated.h"

/**
 * 
 */
UCLASS()
class ANTGAME_API AAntAiController : public AAIController
{
	GENERATED_BODY()

	//Blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName LocationToGoKey;
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey;
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName BridgeKey;

	/*
	Array for the waypoints for the pathfinding
	Stored as an AActor so I can use the GetAllActorsOfClass funtion
	*/
	TArray<AActor*> PatrolPoints;

	/*
	Reference to the behavior tree component
	Used only to kickstart the tree from the possess function
	AntAI holds the behaviortree reference for the logic
	Needs to be serperate because controller inherits aicontroller and cannot be used as a moving object in the world
	*/
	class UBehaviorTreeComponent* BehaviorComp;
	
	/*Posses is executed when the character we want to control is spawned.
	Inside this function, we initialize the blackboard and start the behavior tree*/
	virtual void Possess(APawn* Pawn) override;



public:

	AAntAiController();

	//Functions that get called when noise is heard
	void CommandLeavePlayer(APawn* Pawn);
	void SetPlayerFollow(APawn* Pawn);

	//Reference to blackboard component
	UBlackboardComponent* BlackboardComp;

	//Used to get currentpatrolpoint for blackboard set in BTSelectAntPatrolPoint
	int32 CurrentPatrolPoint = 0;
	//Function to get all patrol points and blackcomponent for use in BTSelectAntPatrolPoint class
	FORCEINLINE UBlackboardComponent* GetBlackBoardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

};