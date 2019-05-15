// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraMovement.h"

// Sets default values
ACameraMovement::ACameraMovement()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	MeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MeshRoot"));
	RootComponent = MeshRoot;

	springArm->AttachTo(RootComponent);
	springArm->TargetArmLength = 350.f;
	springArm->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));

	camera->AttachTo(springArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ACameraMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator newYaw = GetActorRotation();
	newYaw.Yaw += mouseInput.X;
	SetActorRotation(newYaw);
	FRotator newPitch = springArm->GetComponentRotation();
	
	newPitch.Pitch = FMath::Clamp(newPitch.Pitch + mouseInput.Y, -80.f, 0.f);
	springArm->SetWorldRotation(newPitch);

}

// Called to bind functionality to input
void ACameraMovement::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MouseYaw", this, &ACameraMovement::MouseYaw);
	InputComponent->BindAxis("MousePitch", this, &ACameraMovement::MousPitch);
}

void ACameraMovement::MouseYaw(float axis)
{
	mouseInput.X = axis;
}

void ACameraMovement::MousPitch(float axis)
{
	mouseInput.Y = axis;
}


