// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrappleCharacter.h"
#include "GrappleCameraComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UGrappleCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrappleCameraComponent();

	UPROPERTY(EditAnywhere, Category = Camera);
	float MaxLeanDegrees{ 40.0f };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AGrappleCharacter* GrappleCharacter;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
