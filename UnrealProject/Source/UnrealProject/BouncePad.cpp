// Fill out your copyright notice in the Description page of Project Settings.


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

FVector ABouncePad::GetLaunchVector()
{
	FVector verticalForce = GetActorUpVector() * VerticalBoost;
	FVector forwardForce = GetActorForwardVector() * ForwardBoost;
	return verticalForce + forwardForce;
}

