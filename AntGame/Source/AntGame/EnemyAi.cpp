// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAi.h"
#include "EnemyAiController.h"
#include "Waypoint.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AEnemyAi::AEnemyAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create collision box and determine its size
	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	MyBoxComponent->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	RootComponent = MyBoxComponent;

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAi::OnOverlapBegin);
	MyBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyAi::OnOverlapEnd);
	bCanApplyDamage = false;

}

void AEnemyAi::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		bCanApplyDamage = true;
		MyCharacter = Cast<AActor>(OtherActor);
		MyHit = SweepResult;
		GetWorldTimerManager().SetTimer(EnemyTimerHandle, this, &AEnemyAi::ApplyEnemyDamage, 2.6f, true, 0.0f);


	}
}

void AEnemyAi::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCanApplyDamage = false; 
	GetWorldTimerManager().ClearTimer(EnemyTimerHandle);

}

void AEnemyAi::ApplyEnemyDamage()
{
	//this triggers the receivepointdamage on the character side.
	//the 250.0f is the amount of damage the player character receives.
	if (bCanApplyDamage)
	{
		UGameplayStatics::ApplyPointDamage(MyCharacter, 250.0f, GetActorLocation(), MyHit, nullptr, this,
			EnemyDamageType);

	}
}

// Called when the game starts or when spawned
void AEnemyAi::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), Waypoints);
	MoveToWaypoint();
	
}

// Called every frame
void AEnemyAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentWaypoint == 10 && reachedPoint) {
		CurrentWaypoint = 1;
		MoveToWaypoint();
	}

}

/**
 * @brief 
 * Function for AI to keep following waypoints
 */
void AEnemyAi::MoveToWaypoint() 
{
	AEnemyAiController* EnemyAiController = Cast<AEnemyAiController>(GetController());

	if (EnemyAiController) 
	{
		//If not reached the end of the waypoints continue loop
		if (CurrentWaypoint <= Waypoints.Num()) 
		{
			reachedPoint = false;
			for (AActor* Waypoint : Waypoints) 
			{
				AWaypoint* WaypointItr = Cast<AWaypoint>(Waypoint);

				if (WaypointItr) 
				{
					//If currentwaypoint exist in waypoints array move to it
					if (WaypointItr->GetWaypointOrder() == CurrentWaypoint)
					{
						EnemyAiController->MoveToActor(WaypointItr, 1.f, false);
						reachedPoint = true;
						CurrentWaypoint++;
						break;
					}
				}
			}
		}
	}
}

