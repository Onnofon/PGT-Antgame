#define printf(text, fstring)  if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "AntAI.h"
#include "AntAiController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"


/**
 * @brief 
 * Initialize pawnsensingcomp to the component so the values can be set
 */
AAntAI::AAntAI()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
	PawnSensingComp->HearingThreshold = 400.f;
}
/**
 * @brief 
 * Called when the game starts or when spawned Checks for noise and calls OnHearFollowCommand when it hears something
 */
void AAntAI::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnHearNoise.AddDynamic(this, &AAntAI::OnHearFollowCommand);
	}
}


/**
 * @brief 
 * Called when noise/command was heard
 */
void AAntAI::OnHearFollowCommand(APawn * Pawn, const FVector & Location, float Volume)
{
	//Get the AntAiController
	AAntAiController* AIController = Cast<AAntAiController>(GetController());
	//Check if Aicontroller is not null
		if (AIController)
		{
			// Then check if the Ant is already following the player
			// Call the corresponding function and set the bool
			// Functions are in the AntAiController class because it has the references to the blackboard and can update the values
			if (!followingPlayer)
			{
				AIController->SetPlayerFollow(Pawn);
				followingPlayer = true;
			}
			else
			{
				AIController->CommandLeavePlayer(Pawn);
				followingPlayer = false;
			}
		}
}



