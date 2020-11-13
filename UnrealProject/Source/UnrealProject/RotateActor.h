// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActor.generated.h"

UCLASS()
class UNREALPROJECT_API ARotateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotateActor();

	UPROPERTY(EditAnywhere, Category = Rotate);
	AActor* TargetActor;

	// Rotation speed (degrees/second)
	UPROPERTY(EditAnywhere, Category = Rotate);
	float DegreesPerSecond;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
