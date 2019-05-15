// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyAi.generated.h"

UCLASS()
class ANTGAME_API AEnemyAi : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAi();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* MyBoxComponent;

	//create damage type for this enemy
	UPROPERTY(EditAnywhere)
		TSubclassOf<UDamageType> EnemyDamageType;

	UPROPERTY(EditAnywhere)
		AActor* MyCharacter;

	UPROPERTY(EditAnywhere)
		FHitResult MyHit;

	bool bCanApplyDamage;
	FTimerHandle EnemyTimerHandle;

	// declare component overlap begin function
	// declare component overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare component overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
		void ApplyEnemyDamage();

public:
	void MoveToWaypoint();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcces = "true"))
	int CurrentWaypoint;
	bool reachedPoint;
	
	TArray<AActor*> Waypoints;

};
