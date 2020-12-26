// Fill out your copyright notice in the Description page of Project Settings.


#define print(text) UE_LOG(LogTemp, Warning, TEXT(text))
#define printFString(text, fstring) UE_LOG(LogTemp, Warning, TEXT(text), fstring)
#include "PlayerAudioComponent.h"
#include "Components/AudioComponent.h"


// Sets default values for this component's properties
UPlayerAudioComponent::UPlayerAudioComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	MoveComponent = Cast<ACharacter>(GetOwner())->GetCharacterMovement();
	if (!MoveComponent)
	{
		print("PlayerAudioComponent ERROR | could not find CharacterMovementComponent on player character");
	}
	// ...
	
}


// Called every frame
void UPlayerAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UPlayerAudioComponent::CalculateSpeedNormalized(float MaxSpeed)
{
	if (MoveComponent->IsMovingOnGround())
	{
		return 0.0f;
	}

	// Scale speed down by 10
	float speed = GetOwner()->GetVelocity().Size() / 10;

	// Normalize according to MaxSpeed
	float speedNormalized = 1 - ((MaxSpeed - speed) / MaxSpeed);
	return FMath::Abs(speedNormalized);
}

float UPlayerAudioComponent::CalculateSpeedDirectionalNormalized(float MaxSpeed, FVector Direction)
{
	// Get dot product with direction
	//float dot = FMath::Abs(FVector::DotProduct(GetOwner()->GetVelocity(), Direction));
	float dot = FVector::DotProduct(GetOwner()->GetVelocity(), Direction);
	
	// Apply normalizing function
	float speedNormalized = 1 - ((MaxSpeed - dot) / MaxSpeed);
	return speedNormalized;
}


void UPlayerAudioComponent::SpatializeAudio(float SpatialDistance, UAudioComponent* AudioComponent)
{
	// Get normalized direction of character movement
	FVector direction = MoveComponent->GetLastUpdateVelocity().GetSafeNormal();


	// Place audio component in direction of movement (spatializes wind, collision, etc)
	FVector actorPosition = GetOwner()->GetActorLocation();
	FTransform audioTransform = AudioComponent->GetComponentTransform();

	FVector offset = direction * SpatialDistance;
	audioTransform.SetLocation(actorPosition + (offset));
}
