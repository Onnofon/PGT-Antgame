// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveAbleRock.h"
#include <Runtime/Engine/Classes/Components/StaticMeshComponent.h>

/**
 * @brief 
 * Default values of rock set here
 */
AMoveAbleRock::AMoveAbleRock()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

