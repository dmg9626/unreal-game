// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovingGrappleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UMovingGrappleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovingGrappleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Position (relative to local pivot) that grapple beam hooked onto
	FVector RelativeGrapplePoint;

public:	

	// Called when player grapples onto this actor
	UFUNCTION(BlueprintCallable, Category = "Grapple")
	void SetGrapplePoint(FHitResult hit);

	// Returns transformed grapple point
	UFUNCTION(BlueprintCallable, Category = "Grapple")
	FVector GetUpdatedGrapplePoint();
};
