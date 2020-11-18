// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GrappleCharacterMoveComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECustomMovementType : uint8
{
    Swing UMETA(DisplayName = "Swing")
};

struct GrappleData
{
    // Angle along Axis that dictates how "far" the player can swing back and forth
    float SwingHalfAngle;

    // Ranges from 1 to -1, controls direction/rate at which player swings around Axis
    // Positive = forward (i.e. starting swing direction), negative = backwards
    float SwingDirection;

    // Point from which player is grappling
    FVector Point;

    // Axis player is swinging along
    FVector Axis;

    // Stores position from previous frame (to track linear velocity)
    FVector LastPosition;

    // Distance from player to GrapplePoint
    float Distance;
};

UCLASS()
class UNREALPROJECT_API UGrappleCharacterMoveComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
    // Called from GrappleCharacter on BeginPlay()
    UFUNCTION(BlueprintCallable, Category = "Grapple")
    void SetGrappleConstants(const float aSwingSpeed, const float aGrappleReleaseBoost);

    // Called when player starts grappling from a point. Values stored for use in subsequent calls to GrapplePhysCustom()
    void SetGrapple(const FVector aGrapplePoint, const FVector aGrappleAxis, const float aGrappleDistance);
	
protected:

    float SwingSpeed;

    // Scalar value applied to player velocity when launching out of a swing
    float GrappleReleaseBoost;

    GrappleData Grapple;

    virtual void PhysCustom(float deltaTime, int32 Iterations) override;

    void GrapplePhysCustom(float deltaTime, int32 Iterations);

    // Returns angle (in degrees) between current swing vector and downward vector (i.e. how far along the axis you are from the neutral hanging position)
    float CalculateSwingHalfAngle();

    // Called every tick
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

};
