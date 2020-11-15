// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))
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

	//printFString("%s", *GetActorForwardVector().ToString());
}

void AGrappleCharacter::Grapple(float DeltaTime)
{
	// Get (unit) vector from target to self
	FVector unitDelta = (GetActorLocation() - GrapplePoint).GetSafeNormal();

	// Rotate delta vector around our up axis
	FVector unitRevolvedDelta = unitDelta.RotateAngleAxis(SwingSpeed * DeltaTime, GrappleAxis);

	// Calculate new position relative to target
	FVector newPosition = (unitRevolvedDelta * GrappleDistance) + GrapplePoint;
	SetActorLocation(newPosition);
}

FVector AGrappleCharacter::CalculateGrappleAxis(FVector vToGrapplePoint)
{
	FVector axis = FVector::CrossProduct(GetActorForwardVector(), vToGrapplePoint);
	return axis.GetSafeNormal();
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

	if (hit.bBlockingHit)
	{
		// Update grapple settings
		GrapplePoint = hit.Location;
		GrappleAxis = CalculateGrappleAxis(traceDirection.Vector());
		//GrappleAxis = GetActorRightVector();
		GrappleDistance = hit.Distance;
	}

	return hit;
}

// Called to bind functionality to input
void AGrappleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

