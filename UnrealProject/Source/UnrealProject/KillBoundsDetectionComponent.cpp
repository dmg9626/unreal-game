// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) UE_LOG(LogTemp, Warning, TEXT(text))
#define printFString(text, fstring) UE_LOG(LogTemp, Warning, TEXT(text), fstring)
#include "KillBoundsDetectionComponent.h"

// Sets default values for this component's properties
UKillBoundsDetectionComponent::UKillBoundsDetectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKillBoundsDetectionComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UKillBoundsDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

