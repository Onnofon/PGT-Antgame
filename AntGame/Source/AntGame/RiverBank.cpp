// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FColor::Cyan, text)

#include "RiverBank.h"

// Sets default values
ARiverBank::ARiverBank()
{
	OnActorBeginOverlap.AddDynamic(this, &ARiverBank::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &ARiverBank::OffOverlap);
}

void ARiverBank::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		MyAnt = Cast<AMyPawn>(OtherActor);

		if (MyAnt) {
			print("YOOOO");
			MyAnt->closeByRiver = true;
		}
	}
}

void ARiverBank::OffOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		MyAnt = Cast<AMyPawn>(OtherActor);

		if (MyAnt)
		{
			print("BYEEE");
			MyAnt->closeByRiver = false;
		}
	}
}

