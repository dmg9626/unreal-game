// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "BouncePad.generated.h"

UCLASS()
class UNREALPROJECT_API ABouncePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncePad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Controls vertical launch force
	UPROPERTY(EditAnywhere, Category = BouncePad);
	float VerticalBoost{ 1000.0f };

	// Controls forward launch force
	UPROPERTY(EditAnywhere, Category = BouncePad);
	float ForwardBoost{ 1000.0f };

	// When true, launches in direction of BouncePad's forward vector.
	// When false, launches towards Player's forward vector
	UPROPERTY(EditAnywhere, Category = BouncePad);
	bool Directional;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns vector used to launch player
	UFUNCTION(BlueprintCallable, Category = BouncePad)
	FVector GetLaunchVector(ACharacter* character);
};
