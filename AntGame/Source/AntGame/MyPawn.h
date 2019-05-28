// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "MyPawn.generated.h"

class UTimelineComponent;

UCLASS()
class ANTGAME_API AMyPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void Tick(float DeltaTime) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	float jumpAdjust = 3.0f;

	bool bDo;
	bool MaxJumpHeightReached;

	// void myDoOnce();

	// void resetMyDoOnce();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere)
		USceneComponent* OurVisibleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UPawnNoiseEmitterComponent* PawnNoiseEmitterComp;

	void MoveForwards(float AxisValue);
	void MoveBackwards();
	void MoveBackwardsOff();
	void StartGrowing();
	void StopGrowing();
	void GainResources();
	void LoseHealth();
	void CommandFollow();
	void MouseYaw(float axis);
	void MousPitch(float axis);

	UFUNCTION()
		void OnStartJump();

	UFUNCTION()
		void OnStopJump();

	UPROPERTY(EditAnywhere)
		int numberFollowingAnts;

	FVector2D mouseInput;
	FRotator newYaw;
	FRotator newPitch;

	FVector CurrentVelocity;
	bool bGrowing;

	UPROPERTY(EditAnywhere)
		int MovingBackwards = 1;

	//Create values for the resources & the way to integrate them in the UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

		UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		USceneComponent* MeshRoot;

	//UPROPERTY(EditAnywhere)
	//	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		float Resources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		float ResourcesNumber;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		float ResourcesPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		float FullResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		float PreviousResources;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		float ResourcesValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool RedFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		UCurveFloat* ResourcesCurve;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
//		FTimeline MyTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		FTimerHandle MemberTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		FTimerHandle ResourcesTimerHandle;

	//UTimelineComponent* MyTimeline;
	float CurveFloatValue;
	float TimelineValue;
	bool bCanUseResources;

	UTimelineComponent* MyTimeline;

	//struct FTimerHandle MemberTimerHandle;
	//struct FTimerHandle ResourcesTimerHandle;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	UFUNCTION(BlueprintPure, Category = "Resources")
		float GetResources();

	UFUNCTION(BlueprintPure, Category = "Resources")
		FText GetResourcesIntText();

	UFUNCTION()
		void DamageTimer();

	UFUNCTION()
		void SetDamageState();

	UFUNCTION()
		void SetResourcesValue();

	UFUNCTION()
		void SetResourcesState();

	UFUNCTION()
		void SetResourcesChange(float ResourcesChange);

	UFUNCTION()
		void UpdateResources();

	UFUNCTION(BlueprintPure, Category = "Health")
		bool PlayFlash();
		
	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange);





};	
