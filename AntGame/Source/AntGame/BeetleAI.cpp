// Fill out your copyright notice in the Description page of Project Settings.
#define printf(text, fstring)  if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "BeetleAI.h"
#include "BeetleAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

/**
 * @brief 
 * Initialize pawnsensing component and set values
 */
ABeetleAI::ABeetleAI()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
}

/**
 * @brief 
 * Called when the game starts or when spawned Checks for other actors in his sight.
 */
void ABeetleAI::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ABeetleAI::OnPlayerCaught);
	}
}

/**
 * @brief 
 * Called when a player has been spotted \n
 * Calls function in AiController class \n
 * Functions are in the BeetkeAiController class because it has the references to the blackboard and can update the values
 */
void ABeetleAI::OnPlayerCaught(APawn * Pawn)
{
	ABeetleAIController* AIController = Cast<ABeetleAIController>(GetController());
	if (AIController)
	{
		printf("You have been caught", *Pawn->GetName());
		AIController->SetPlayerCaught(Pawn);
	}
}

