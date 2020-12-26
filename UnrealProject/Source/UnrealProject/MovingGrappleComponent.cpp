// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) UE_LOG(LogTemp, Warning, TEXT(text))
#define printFString(text, fstring) UE_LOG(LogTemp, Warning, TEXT(text), fstring)
#include "MovingGrappleComponent.h"

// Sets default values for this component's properties
UMovingGrappleComponent::UMovingGrappleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovingGrappleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMovingGrappleComponent::SetGrapplePoint(FHitResult hit)
{
	if (!hit.bBlockingHit)
	{
		print("WARNING: MovingGrappleComponent.SetGrapplePoint() called with non-blocking FHitResult");
		return;
	}

	// Store relative position of grapple point
	RelativeGrapplePoint = hit.ImpactPoint - GetOwner()->GetActorLocation();

	// Store rotation at beginning of grapple, so we can track change in rotation over time
	InitialRotation = GetOwner()->GetActorRotation();
}

