// Fill out your copyright notice in the Description page of Project Settings.
#define printf(text, fstring)  if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include <Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "Components/InputComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TimelineComponent.h"
#include <Runtime/Engine/Classes/Components/PawnNoiseEmitterComponent.h>
#include "AntAI.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComp"));

	//UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	//OurCamera->SetupAttachment(RootComponent);
	//OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	//OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//MeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MeshRoot"));
	//RootComponent = MeshRoot;

	springArm->AttachTo(RootComponent);
	springArm->TargetArmLength = 350.f;
	springArm->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));

	camera->AttachTo(springArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Health logics
	FullHealth = 1000.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;
	bCanBeDamaged = true;

	//Resource logics
	//Fullresources depends on the level you are currently in and the max amount of possible resources you can get in it
	FullResources = 100.0f;
	Resources = 0.0f;
	PreviousResources = ResourcesPercentage;
	ResourcesValue = 0.0f;
	
	if (ResourcesCurve) {
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;
		TimelineCallback.BindUFunction(this, FName("SetResourcesValue"));
		TimelineFinishedCallback.BindUFunction(this, FName("SetResourcesState"));
		MyTimeline = NewObject<UTimelineComponent>(this, FName("Resources Animation"));
		MyTimeline->AddInterpFloat(ResourcesCurve, TimelineCallback);
		MyTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
		MyTimeline->RegisterComponent();
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing) {
		CurrentScale += DeltaTime;
	}
	else {
		CurrentScale -= (DeltaTime * 0.5f);
	}

	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	//OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	if (MyTimeline != nullptr) MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);

	Super::Tick(DeltaTime);
	FRotator newYaw = GetActorRotation();
	newYaw.Yaw += mouseInput.X;
	SetActorRotation(newYaw);
	FRotator newPitch = springArm->GetComponentRotation();

	newPitch.Pitch = FMath::Clamp(newPitch.Pitch + mouseInput.Y, -80.f, 0.f);
	springArm->SetWorldRotation(newPitch);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("Command_Follow", IE_Pressed, this, &AMyPawn::CommandFollow);
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
	InputComponent->BindAxis("MouseYaw", this, &AMyPawn::MouseYaw);
	InputComponent->BindAxis("MousePitch", this, &AMyPawn::MousPitch);
}

void AMyPawn::Move_XAxis(float AxisValue) {
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue) {
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

/*void AMyPawn::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (MyTimeline != nullptr) MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
} */

void AMyPawn::StartGrowing() {
	bGrowing = true;
}

void AMyPawn::StopGrowing() {
	bGrowing = false;
}
void AMyPawn::MouseYaw(float axis){
	mouseInput.X = axis;
}

void AMyPawn::MousPitch(float axis){
	mouseInput.Y = axis;
}

void AMyPawn::CommandFollow()
{
	MakeNoise(1.0f, this, FVector::ZeroVector);
}

//This class is used for adding resources 
void AMyPawn::GainResources() {

	UWorld* const World = GetWorld();

	//On collision with homebase with a resource carried; put this in the if condition
	//if ()
	//{
		//play animation if specified
		//play sound if specified

	if (MyTimeline != nullptr) MyTimeline->Stop();
		GetWorldTimerManager().ClearTimer(ResourcesTimerHandle);
		SetResourcesChange(+20.0f);
		GetWorldTimerManager().SetTimer(ResourcesTimerHandle, this, &AMyPawn::UpdateResources,
			5.0f, false);
	//}
}

//This class is used for reducing health when hit by an enemy/environmental hazard
void AMyPawn::LoseHealth() {

}

//Get the current health percentage
float AMyPawn::GetHealth()
{

	return HealthPercentage;
}

float AMyPawn::GetResources()
{
	return ResourcesPercentage;
}

FText AMyPawn::GetHealthIntText()
{
	int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString HPS = FString::FromInt(HP);
	FString HealthHUD = HPS + FString(TEXT("%"));
	FText HPTEXT = FText::FromString(HealthHUD);
	return HPTEXT;
}

FText AMyPawn::GetResourcesIntText()
{
	int32 MP = FMath::RoundHalfFromZero(ResourcesPercentage * 100);
	FString MPS = FString::FromInt(MP);
	//Full resources, maybe per level?
	FString FullMPS = FString::FromInt(FullResources);

	FString ResourcesHUD = MPS + FString(TEXT("/") + FullMPS);
	FText ResourcesTEXT = FText::FromString(ResourcesHUD);
	return ResourcesTEXT;
}

//Telling the game the player character can now be damaged
void AMyPawn::SetDamageState()
{
	bCanBeDamaged = true;

}

void AMyPawn::DamageTimer()
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMyPawn::SetDamageState, 2.0f, false);
}

void AMyPawn::SetResourcesValue()
{
	TimelineValue = MyTimeline->GetPlaybackPosition();	
	//Error message, but should be able to compile properly
	CurveFloatValue = PreviousResources + ResourcesValue*ResourcesCurve->GetFloatValue(TimelineValue);
	Resources = CurveFloatValue * FullHealth;
	Resources = FMath::Clamp(Resources, 0.0f, FullResources);
	ResourcesPercentage = CurveFloatValue;
	ResourcesPercentage = FMath::Clamp(ResourcesPercentage, 0.0f, 1.0f);
}

void AMyPawn::SetResourcesState()
{
	bCanUseResources = true;
	ResourcesValue = 0.0f;
	//If want to change the ant model when returning resources, we do it here.
}

//flash in screen for when player takes damage
bool AMyPawn::PlayFlash()
{
	if (RedFlash)
	{
		RedFlash = false;
		return true;
	}

	return false;
}

float AMyPawn::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	bCanBeDamaged = false;
	RedFlash = true;
	UpdateHealth(-DamageAmount);
	DamageTimer();
	return DamageAmount;
}

void AMyPawn::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;
}

void AMyPawn::UpdateResources()
{
	PreviousResources = ResourcesPercentage;
	ResourcesPercentage = Resources / FullResources;
	ResourcesValue = 1.0f;
	//This will fill up the resourcebar
	if (MyTimeline != nullptr) MyTimeline->PlayFromStart();
}

void AMyPawn::SetResourcesChange(float ResourcesChange)
{
	bCanUseResources = false;
	PreviousResources = ResourcesPercentage;
	ResourcesValue = ResourcesChange / FullResources;
	
	if (MyTimeline != nullptr) MyTimeline->PlayFromStart();

}