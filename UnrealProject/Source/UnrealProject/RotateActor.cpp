// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateActor.h"

// Sets default values
ARotateActor::ARotateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetActor)
		return;

	// Get vector from target to self
	FVector delta = GetActorLocation() - TargetActor->GetActorLocation();

	// Rotate delta vector around our up axis
	FVector newDelta = delta.RotateAngleAxis(DegreesPerSecond * DeltaTime, GetActorUpVector());

	// Calculate new position relative to target
	FVector newPosition = newDelta + TargetActor->GetActorLocation();
	SetActorLocation(newPosition);
}

