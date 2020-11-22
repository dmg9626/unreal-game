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
	AGrappleCharacter();
	//AGrappleCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Grapple);
	float GrappleRange{ 1000.0f };

	// Controls strength of tension force during grappling.
	UPROPERTY(EditAnywhere, Category = Grapple);
	float GrappleTensionWeight{ 2.0f };

	// Controls amount of forward momentum applied during swinging.
	// Generally, higher value = higher acceleration
	UPROPERTY(EditAnywhere, Category = Grapple);
	float ForwardMomentumWeight{ 70000.0f };

	// Radius of sphere used to find grapple hit results. 
	// Larger radius = more lenient, smaller = more precise
	UPROPERTY(EditAnywhere, Category = Grapple);
	float SphereTraceRadius{ 15.0f };

	// Factor by which to reduce tension force pushing against the player (i.e. "pole-vaulting" effect).
	// Higher value => smaller force
	UPROPERTY(EditAnywhere, Category = Grapple);
	float InverseTensionDampeningFactor{ 2.0f };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = Grapple);
	bool IsGrappling{ false };
	
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = Grapple);
	FVector GrapplePoint;

	// Calculates force of grapple tension
	FVector CalculateTensionForce();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Returns raycast hit result for a grapple target within GrappleRange in player-facing direction */
	UFUNCTION(BlueprintCallable, Category = "Grapple")
	bool TryGrapple();

	UFUNCTION(BlueprintCallable, Category = "Grapple")
	FVector CalculateGrappleForce();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool CursorTargetInRange();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
