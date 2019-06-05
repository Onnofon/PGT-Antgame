// Fill out your copyright notice in the Description page of Project Settings.

#include "Resources1.h"

// Sets default values
AResources1::AResources1()
{
	
	OnActorBeginOverlap.AddDynamic(this, &AResources1::OnOverlap);



}

void AResources1::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		MyCharacter = Cast<AMyPawn>(OtherActor);

		if (MyCharacter && MyCharacter->GetResources() < 1.0f)
		{
			//100 is the value that gets added to the resources.
			MyCharacter->SetResourcesChange(25.0f);
			Destroy();
		}
	}
}

