/// <summary>
/// Standard triggerbox for detecting collision \n Inherits from ATriggerBox for detection
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class ANTGAME_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	AMyTriggerBox();


	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
