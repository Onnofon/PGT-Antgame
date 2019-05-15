// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyPawn.h"
#include "Engine/World.h"

#include "AntGameGameModeBase.generated.h"

UENUM()
enum class EGamePlayState
{
	EPlaying,
	EGameOver,
	EUnknown
};


UCLASS()
class ANTGAME_API AAntGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAntGameGameModeBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	AMyPawn* MyPawn;

	UFUNCTION(BlueprintPure, Category = "Health")
		EGamePlayState GetCurrentState() const;

	void SetCurrentState(EGamePlayState NewState);

private:

	EGamePlayState CurrentState;

	void HandleNewState(EGamePlayState NewState);

};
