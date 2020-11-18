// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GrappleCharacterMoveComponent.h"
#include "GrappleCharacter.generated.h"

UCLASS()
class UNREALPROJECT_API AGrappleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//AGrappleCharacter();
	AGrappleCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Grapple);
	float GrappleRange{ 1000.0f };

	APlayerController* PlayerController;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Pointer to custom move component
	class UGrappleCharacterMoveComponent* MovementComponent;

	// Returns camera pitch in degrees, between -180 and 180
	float GetPitchNormalized();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector CalculateGrappleAxis(FVector vToGrapplePoint);

	UFUNCTION(BlueprintCallable, Category = "Grapple")
	bool IsGrappling();

	UFUNCTION(BlueprintCallable, Category = "Grapple")
	void StopGrappling();

	/* Returns raycast hit result for a grapple target within GrappleRange in player-facing direction */
	UFUNCTION(BlueprintCallable, Category = "Grapple")
	FHitResult TryGrapple();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
