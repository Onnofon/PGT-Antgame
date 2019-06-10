// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Cyan, text)

#include "WaterCollision.h"

AWaterCollision::AWaterCollision()
{
	OnActorBeginOverlap.AddDynamic(this, &AWaterCollision::OnOverlap);
}

void AWaterCollision::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		MyAnt = Cast<AMyPawn>(OtherActor);

		if (MyAnt)
		{
			MyAnt->TakeDamage(400.0f);
		}
	}
}

