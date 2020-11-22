// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) UE_LOG(LogTemp, Warning, TEXT(text))
#define printFString(text, fstring) UE_LOG(LogTemp, Warning, TEXT(text), fstring)
#include "BouncePad.h"

// Sets default values
ABouncePad::ABouncePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABouncePad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABouncePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABouncePad::GetLaunchVector(ACharacter* character)
{
	// Make sure we have a valid character reference
	if (!character)
	{
		print("ERROR: BouncePad received null reference to character. Check the character blueprint to ensure the character is being plugged in as an argument to GetLaunchVector().");
		return FVector::ZeroVector;
	}

	FVector verticalForce = FVector(1.0f) * VerticalBoost;
	FVector forwardForce = FVector(1.0f) * ForwardBoost;

	// Select orientation of forward force based on Directional setting
	if (Directional)
	{
		// Use bounce pad's forward orientation
		forwardForce *= GetActorForwardVector();
	}
	else
	{
		// Use character's forward orientation
		forwardForce *= character->GetActorForwardVector();
	}

	// Always use bounce pad's local up vector (allows for angled bounce pads to behave like you'd expect)
	verticalForce *= GetActorUpVector();

	return verticalForce + forwardForce;
}

