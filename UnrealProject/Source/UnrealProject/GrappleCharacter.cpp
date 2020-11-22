// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) UE_LOG(LogTemp, Warning, TEXT(text))
#define printFString(text, fstring) UE_LOG(LogTemp, Warning, TEXT(text), fstring)
#include "GrappleCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Initialize with our custom CharacterMovementComponent
AGrappleCharacter::AGrappleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGrappleCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void AGrappleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AGrappleCharacter::CalculateGrappleForce()
{
	// Calculate force of tension
	FVector grappleTension = CalculateTensionForce();

	// Add forward momentum
	FVector forwardMomentum = GetActorForwardVector() * ForwardMomentumWeight;

	return grappleTension + forwardMomentum;
}

bool AGrappleCharacter::CursorTargetInRange()
{
	FHitResult hit(ForceInit);

	// Initialize raycast values from player perspective
	FVector traceStart;
	FRotator traceDirection;

	PlayerController->GetPlayerViewPoint(traceStart, traceDirection);
	FVector traceEnd = traceStart + (traceDirection.Vector() * GrappleRange);

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(TryGrapple), true, GetInstigator());

	// Perform raycast and return hit result
	GetWorld()->LineTraceSingleByChannel(hit, traceStart, traceEnd, ECC_Visibility, traceParams);
	return hit.bBlockingHit;
}

FVector AGrappleCharacter::CalculateTensionForce()
{
	// Vector from hook point to player
	FVector hookToPlayer = GetActorLocation() - GrapplePoint;

	// Calculate dot product with current velocity
	float dot = FVector::DotProduct(hookToPlayer, GetVelocity());

	// Scale hookToPlayer's length to resulting dot product
	FVector scaledByDot = hookToPlayer.GetSafeNormal() * dot;

	// Reverse direction and scale by this force's weight
	FVector grappleTension = -scaledByDot * GrappleTensionWeight;

	// If tension force is pushing against player (happens when moving towards hook point)
	float forceDirection = FVector::DotProduct(hookToPlayer, GetVelocity());
	if (!FMath::IsNearlyZero(forceDirection) && forceDirection < 0)
	{
		// Scale force down by dampening factor
		grappleTension /= InverseTensionDampeningFactor;
	}

	return grappleTension;
}

bool AGrappleCharacter::TryGrapple()
{
	FHitResult hit(ForceInit);

	// Find/validate player controller instance
	if (!PlayerController)
	{
		return false;
	}

	// Initialize raycast values from player perspective
	FVector traceStart;
	FRotator traceDirection;

	PlayerController->GetPlayerViewPoint(traceStart, traceDirection);
	FVector traceEnd = traceStart + (traceDirection.Vector() * GrappleRange); // TODO: make distance a variable

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(TryGrapple), true, GetInstigator());

	// Perform sphere trace
	//bool hitReturned = GetWorld()->SweepSingleByChannel(hit, traceStart, traceEnd, traceDirection.Quaternion(), ECC_Visibility, FCollisionShape::MakeSphere(SphereTraceRadius));
	//if (hitReturned)
	//{
	//	FVector GrapplePoint = hit.ImpactPoint;
	//}

	TArray<AActor*> actorsToIgnore{ this };
	bool hitReturned = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), traceStart, traceEnd, SphereTraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false, actorsToIgnore, EDrawDebugTrace::ForDuration, hit, true);
	
	GrapplePoint = hit.ImpactPoint;
	IsGrappling = hitReturned;

	return hitReturned;
}

// Called to bind functionality to input
void AGrappleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

