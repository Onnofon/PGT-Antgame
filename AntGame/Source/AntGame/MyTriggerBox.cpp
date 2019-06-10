#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Cyan, text)
#define printf(text, fstring)  if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Cyan, FString::Printf(TEXT(text), fstring))

#include "MyTriggerBox.h"
#include "DrawDebugHelpers.h"


/**
 * @brief 
 * Used for adding dynamic to OnOverlapBegin and OnOverEnd so it can detect overlap
 */
AMyTriggerBox::AMyTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
}

/**
 * @brief 
 * Called on start game
 */
void AMyTriggerBox::BeginPlay() 
{

	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0 , 5);
}

/**
 * @brief 
 * Detect when overlap is happening then performs next action
 */
void AMyTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) 
{
	if (OtherActor && (OtherActor != this)) 
	{
		print("Overlap appeared");
		printf("Overlapped Actor = %s", *OtherActor->GetName());
	}
}

/**
 * @brief 
 * Detect when overlap has ended then performs next action
 */
void AMyTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor) 
{
	if (OtherActor && (OtherActor != this))
	{
		print("Overlap ended");
		printf("Overlapped Actor = %s", *OverlappedActor->GetName());
	}
}