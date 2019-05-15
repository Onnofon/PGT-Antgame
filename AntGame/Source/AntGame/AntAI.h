// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AntAI.generated.h"

UCLASS()
class ANTGAME_API AAntAI : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AAntAI();

	//Bool used to check if the player is already following for OnHearFollowCommand function
	UPROPERTY(EditAnywhere, Category = AI)
		bool followingPlayer = false;


	//A reference to the behavior tree to use it's logic
	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;

	//A Pawn Noise sensing component which is used in order hear sounds made by the player
	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSensingComp;


private:

	//Function to decide what the ant needs to do when hearing noise
	UFUNCTION()
		void OnHearFollowCommand(APawn* Pawn, const FVector &Location, float Volume);

};
