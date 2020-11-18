// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))
#include "GrappleCharacter.h"
#include "GrappleCharacterMoveComponent.h"

void UGrappleCharacterMoveComponent::SetGrappleConstants(const float aSwingSpeed, const float aGrappleReleaseBoost)
{
    SwingSpeed = aSwingSpeed;
    GrappleReleaseBoost = aGrappleReleaseBoost;
    printFString("Initialized grapple consts: speed = %f", SwingSpeed);
    printFString("Initialized grapple consts: GrappleReleaseBoost = %f", GrappleReleaseBoost);
}

void UGrappleCharacterMoveComponent::SetGrapple(const FVector aGrapplePoint, const FVector aGrappleAxis, const float aGrappleDistance)
{
    Grapple.Point = aGrapplePoint;
    Grapple.Axis = aGrappleAxis;
    Grapple.Distance = aGrappleDistance;
    Grapple.SwingHalfAngle = CalculateSwingHalfAngle();
    Grapple.SwingDirection = 1.0f;
    
    printFString("Swing half-angle = %f", Grapple.SwingHalfAngle);
}

void UGrappleCharacterMoveComponent::PhysCustom(float deltaTime, int32 Iterations)
{
    Super::PhysCustom(deltaTime, Iterations);

    if (CustomMovementMode == static_cast<int>(ECustomMovementType::Swing))
    {
        GrapplePhysCustom(deltaTime, Iterations);
    }
}

void UGrappleCharacterMoveComponent::GrapplePhysCustom(float deltaTime, int32 Iterations)
{
    // If angle between player and gravity exceeds the initial value, start swinging the other direction next frame
    float angleWithGravity = CalculateSwingHalfAngle();
    if (angleWithGravity >= Grapple.SwingHalfAngle)
    {
        Grapple.SwingDirection *= -1;
    }

    // Store position from last frame (so we can track player velocity)
    Grapple.LastPosition = GetLastUpdateLocation();

    // Get (unit) vector from target to self
    FVector unitDelta = (Grapple.LastPosition - Grapple.Point).GetSafeNormal();

    // Rotate delta vector around our up axis
    float angleDelta = SwingSpeed * Grapple.SwingDirection * deltaTime;
    FVector unitRevolvedDelta = unitDelta.RotateAngleAxis(angleDelta, Grapple.Axis);

    // Calculate new position relative to target
    FVector newPosition = (unitRevolvedDelta * Grapple.Distance) + Grapple.Point;

    CharacterOwner->SetActorLocation(newPosition);
}

float UGrappleCharacterMoveComponent::CalculateSwingHalfAngle()
{
    // Calculate half-angle between down-vector and player's starting grapple position
    const FVector grapplePointToPlayer = (CharacterOwner->GetActorLocation() - Grapple.Point).GetSafeNormal();
    const FVector gravityVector = FVector::DownVector;

    float dot = FVector::DotProduct(grapplePointToPlayer, gravityVector);
    float radians = FMath::Acos(dot);

    return FMath::RadiansToDegrees(radians);
}

void UGrappleCharacterMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrappleCharacterMoveComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
    Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

    // If player let go of grapple, apply launch velocity
    // TODO: don't launch player when they release grapple on ground
    if (PreviousMovementMode == EMovementMode::MOVE_Custom)
    {
        FVector launchVector = (CharacterOwner->GetActorLocation() - Grapple.LastPosition) * GrappleReleaseBoost;
        CharacterOwner->LaunchCharacter(launchVector, false, false);
    }
}

