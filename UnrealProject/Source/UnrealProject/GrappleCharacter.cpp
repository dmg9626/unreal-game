// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) UE_LOG(LogTemp, Warning, TEXT(text))
#define printFString(text, fstring) UE_LOG(LogTemp, Warning, TEXT(text), fstring)
#include "GrappleCharacter.h"
#include "KillBoundsDetectionComponent.h"
#include "PlayerAudioComponent.h"
#include "UObject/UObjectBaseUtility.h"
#include "Kismet/KismetSystemLibrary.h"

//// Initialize with our custom CharacterMovementComponent
//AGrappleCharacter::AGrappleCharacter()
//{
//	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//}

AGrappleCharacter::AGrappleCharacter(const class FObjectInitializer& ObjectInitializer)
{
	ObjectInitializer.CreateDefaultSubobject<UKillBoundsDetectionComponent>(this, TEXT("KillBoundsDetection"));
	ObjectInitializer.CreateDefaultSubobject<UPlayerAudioComponent>(this, TEXT("PlayerAudioComponent"));
	
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

void AGrappleCharacter::GetTraceParameters(FVector &traceStart, FVector &traceEnd)
{
	// Initialize raycast values from player perspective
	FRotator traceDirection;

	PlayerController->GetPlayerViewPoint(traceStart, traceDirection);
	traceEnd = traceStart + (traceDirection.Vector() * GrappleRange);
}

FHitResult AGrappleCharacter::GetGrappleTarget(bool sphereTrace = false)
{
	FHitResult hit(ForceInit);

	// Find/validate player controller instance
	if (!PlayerController)
	{
		return hit;
	}

	// Get start/end points
	FVector traceStart, traceEnd;
	GetTraceParameters(traceStart, traceEnd);

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(GetGrappleTarget), true, GetInstigator());

	// Only perform sphere trace if specified (more accurate, but less performant than line trace)
	if (sphereTrace)
	{
		TArray<AActor*> actorsToIgnore{ this };
		bool hitReturned = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), traceStart, traceEnd, SphereTraceRadius,
			UEngineTypes::ConvertToTraceType(ECC_Visibility), false, actorsToIgnore, EDrawDebugTrace::None, hit, true);
	}
	// Otherwise do linetrace
	else
	{
		GetWorld()->LineTraceSingleByChannel(hit, traceStart, traceEnd, ECC_Visibility, traceParams);
	}
	
	// Return hit result
	return hit;
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

FVector AGrappleCharacter::CalculateForwardForce()
{
	return GetActorForwardVector() * ForwardMomentumWeight;
}

FHitResult AGrappleCharacter::TryGrapple()
{
	// Try to find grapple target using sphere trace
	FHitResult hit = GetGrappleTarget(true);
	
	// Store grapple point
	GrapplePoint = hit.ImpactPoint;
	IsGrappling = hit.bBlockingHit;

	// If valid hit returned, check if it's a MovingGrappleActor
	AActor* hitActor = hit.GetActor();
	if (IsGrappling && hitActor != nullptr)
	{
		UActorComponent* component = hitActor->FindComponentByClass(UMovingGrappleComponent::StaticClass());
		if (component)
		{
			// Store reference to moving target
			MovingGrappleTarget = Cast<UMovingGrappleComponent>(component);

			// Pass hit result to target, so it can recalculate GrapplePoint according to movement/rotation
			MovingGrappleTarget->SetGrapplePoint(hit);
		}
	}

	return hit;
}

void AGrappleCharacter::StopGrappling()
{
	// Clear grappling flag and MovingGrappleTarget reference
	IsGrappling = false;
	MovingGrappleTarget = nullptr;
}

void AGrappleCharacter::SetJumpCurrentCount(int count)
{
	JumpCurrentCount = count;
}

// Called to bind functionality to input
void AGrappleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

