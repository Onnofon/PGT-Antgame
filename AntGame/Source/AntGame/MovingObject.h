/// <summary>
/// First prototype for creating a flying objects with detecting not in use
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObject.generated.h"

UCLASS()
class ANTGAME_API AMovingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	int RandomNumber;
	int DirectionX = 1;
	int DirectionY = 1;

	UPROPERTY(EditAnywhere)
	int WorldBoundaryMinusX;
	UPROPERTY(EditAnywhere)
	int WorldBoundaryPlusX;
	UPROPERTY(EditAnywhere)
	int WorldBoundaryMinusY;
	UPROPERTY(EditAnywhere)
	int WorldBoundaryPlusY;
	UPROPERTY(EditAnywhere)
	int SpeedModifier;
	UPROPERTY(EditAnywhere)
	int RandomNumberRange;

};
