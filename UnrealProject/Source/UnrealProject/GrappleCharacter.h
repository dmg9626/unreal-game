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

	UPROPERTY(EditAnywhere, Category = Grapple);
	float GrappleTensionWeight{ 2.0f };

	UPROPERTY(EditAnywhere, Category = Grapple);
	float ForwardMomentumWeight{ 70000.0f };

	UPROPERTY(EditAnywhere, Category = Grapple);
	float SphereTraceRadius{ 15.0f };

	

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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
