// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraMovement.generated.h"


UCLASS()
class ANTGAME_API ACameraMovement : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MouseYaw(float axis);
	void MousPitch(float axis);

	//vector mouse x, y
	FVector2D mouseInput;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		USceneComponent* MeshRoot;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh; 
};
