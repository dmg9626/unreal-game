// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KillBoundsDetectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UKillBoundsDetectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKillBoundsDetectionComponent();

	// Number of kill boundary triggers currently overlapping the actor.
	// When this reaches 0, the actor is respawned at the player spawn point.
	UPROPERTY(BlueprintReadWrite, Category = KillBounds);
	int OverlappingKillBounds;

	UPROPERTY(BlueprintReadWrite, Category = KillBounds);
	FVector SpawnPosition;

	UPROPERTY(BlueprintReadWrite, Category = KillBounds);
	FRotator SpawnRotation;
	
	// Position / rotation to respawn player at
	UPROPERTY(BlueprintReadWrite, Category = KillBounds);
	FTransform SpawnTransform;

	// Number of kill bounds in the current level.
	// If this is 0, respawning is disabled for this level.
	UPROPERTY(BlueprintReadWrite, Category = KillBounds);
	int KillBoundsInLevel{ 0 };

	// True if kill bounds are present in level, false otherwise.
	// If false, player does not respawn when falling out of level.
	UPROPERTY(BlueprintReadWrite, Category = KillBounds);
	bool KillBoundsExist{ false };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
