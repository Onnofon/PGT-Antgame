/// <summary>
/// Acts at the object in the world and sends information to brain class Inherits from ACharacter because it will be interacting with objects in the game \n Brain class is seperate to avoid making one big class which does everything the brain class also does not need the ACharacter inheritance but instead AIController
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BeetleAI.generated.h"

UCLASS()
class ANTGAME_API ABeetleAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABeetleAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);
	//A reference to the behavior tree to use it's logic
	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;

	//A Pawn Noise sensing component which is used in order to see the player
	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSensingComp;

private:

	//Function to decide what to do when player is in sight
	

};
