/// <summary>
/// Actor that acts as object that can be pushed by player \n Just the object real changes happen in Player class (Weight)
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveAbleRock.generated.h"

UCLASS()
class ANTGAME_API AMoveAbleRock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveAbleRock();

protected:

public:	
	// Called every frame
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

};
