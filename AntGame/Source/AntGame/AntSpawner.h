/// <summary>
/// Objects for spawning the Ant AI blueprints for populating the world \n Inherits from Character because will be placed in world.
/// </summary>

#pragma once
#include "AntAI.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AntSpawner.generated.h"

UCLASS()
class ANTGAME_API AAntSpawner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAntSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) 
		TSubclassOf<class AAntAI> ToSpawn;
	UPROPERTY(EditAnywhere)
		int currentAnts;
	UPROPERTY(EditAnywhere)
		int maxAnts;
	UPROPERTY(EditAnywhere)
		int minTimeDelay;
	UPROPERTY(EditAnywhere)
		int maxTimeDelay;
	UPROPERTY(EditAnywhere)
		int delay;

	UFUNCTION(BlueprintCallable)
	void Spawn();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
