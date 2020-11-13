// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleCharacter.h"

// Sets default values
AGrappleCharacter::AGrappleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrappleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrappleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrappleCharacter::Grapple(FVector GrapplePoint, float DeltaTime)
{
	// Get vector from target to self
	FVector delta = GetActorLocation() - GrapplePoint;

	// Rotate delta vector around our up axis
	FVector newDelta = delta.RotateAngleAxis(SwingSpeed * DeltaTime, GetActorRightVector());

	// Calculate new position relative to target
	FVector newPosition = newDelta + GrapplePoint;
	SetActorLocation(newPosition);
}

FHitResult AGrappleCharacter::TryGrapple()
{
	FHitResult hit(ForceInit);

	// Find/validate player controller instance
	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();
	if (!playerController)
	{
		return hit;
	}

	// Initialize raycast values from player perspective
	FVector traceStart;
	FRotator traceDirection;

	playerController->GetPlayerViewPoint(traceStart, traceDirection);
	FVector traceEnd = traceStart + (traceDirection.Vector() * GrappleRange); // TODO: make distance a variable

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(TryGrapple), true, GetInstigator());

	// Perform raycast and return hit result
	GetWorld()->LineTraceSingleByChannel(hit, traceStart, traceEnd, ECC_Visibility, traceParams);
	return hit;
}

// Called to bind functionality to input
void AGrappleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

