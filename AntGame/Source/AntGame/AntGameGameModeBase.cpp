// Fill out your copyright notice in the Description page of Project Settings.

#include "AntGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyPawn.h"
#include "MyHUD.h"
#include "Engine/World.h"


AAntGameGameModeBase::AAntGameGameModeBase()
	: Super()
{
	HUDClass = AMyHUD::StaticClass();

}

void AAntGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetCurrentState(EGamePlayState::EPlaying);

	MyPawn = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AAntGameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetWorld() -> GetMapName();
	if (MyPawn)
	{
		if (FMath::IsNearlyZero(MyPawn->GetHealth(), 0.001f))
		{
			SetCurrentState(EGamePlayState::EGameOver);
		}
	}
}

EGamePlayState AAntGameGameModeBase::GetCurrentState() const
{
	return CurrentState;

}

void AAntGameGameModeBase::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void AAntGameGameModeBase::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
		{
			//do nothing
		}
		break;

	case EGamePlayState::EGameOver:
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
	break;

	default:
	case EGamePlayState::EUnknown:
	{
		// do nothing
	}
	}
}
