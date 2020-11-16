// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GrappleCharacter.generated.h"

UCLASS()
class UNREALPROJECT_API AGrappleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGrappleCharacter();

	UPROPERTY(EditAnywhere, Category = Grapple);
	float SwingSpeed;

	UPROPERTY(EditAnywhere, Category = Grapple);
	float GrappleRange{ 1000.0f };

	// Controls whether Grapple() is called each tick
	UPROPERTY(BlueprintReadWrite, Category = Grapple);
	bool IsGrappling{ false };

	// True when player is in the air and can double jump
	UPROPERTY(BlueprintReadWrite, Category = Grapple);
	bool CanDoubleJump{ false };

	UPROPERTY(BlueprintReadWrite, Category = Grapple);
	FVector GrapplePoint;

	UPROPERTY(BlueprintReadWrite, Category = Grapple);
	FVector GrappleAxis;

	// Current distance from GrapplePoint
	float GrappleDistance;

	// Scalar value applied to player velocity when launching out of a swing
	UPROPERTY(BlueprintReadWrite, Category = Grapple);
	float GrappleReleaseBoost{ 100.0f };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = Grapple);
	FVector LastPosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Grapple(float DeltaTime);

	FVector CalculateGrappleAxis(FVector vToGrapplePoint);

	/* Returns raycast hit result for a grapple target within GrappleRange in player-facing direction */
	UFUNCTION(BlueprintCallable, Category = "Grapple")
	FHitResult TryGrapple();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
