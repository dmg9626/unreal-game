// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))
#include "GrappleCharacter.h"

// Initialize with our custom CharacterMovementComponent
AGrappleCharacter::AGrappleCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UGrappleCharacterMoveComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get pointer to movement component
	UGrappleCharacterMoveComponent* CharacterMovementComponent = Cast<UGrappleCharacterMoveComponent>(GetCharacterMovement());
	check(CharacterMovementComponent != nullptr);
	MovementComponent = CharacterMovementComponent;
}

// Called when the game starts or when spawned
void AGrappleCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
}

float AGrappleCharacter::GetPitchNormalized()
{
	// Get camera rotation
	FVector position;
	FRotator rotation;

	PlayerController->GetPlayerViewPoint(position, rotation);
	return FRotator::NormalizeAxis(rotation.Pitch);
}

// Called every frame
void AGrappleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AGrappleCharacter::CalculateGrappleAxis(FVector vToGrapplePoint)
{
	FVector axis = FVector::CrossProduct(GetActorForwardVector(), vToGrapplePoint);
	return axis.GetSafeNormal();
}

bool AGrappleCharacter::IsGrappling()
{
	return MovementComponent->MovementMode == EMovementMode::MOVE_Custom && MovementComponent->CustomMovementMode == static_cast<int>(ECustomMovementType::Swing);
}

void AGrappleCharacter::StopGrappling()
{
	MovementComponent->SetDefaultMovementMode();
}

FHitResult AGrappleCharacter::TryGrapple()
{
	FHitResult hit(ForceInit);

	// Find/validate player controller instance
	if (!PlayerController)
	{
		return hit;
	}

	// Initialize raycast values from player perspective
	FVector traceStart;
	FRotator traceDirection;

	PlayerController->GetPlayerViewPoint(traceStart, traceDirection);
	FVector traceEnd = traceStart + (traceDirection.Vector() * GrappleRange); // TODO: make distance a variable

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(TryGrapple), true, GetInstigator());

	// Perform raycast and return hit result
	GetWorld()->LineTraceSingleByChannel(hit, traceStart, traceEnd, ECC_Visibility, traceParams);

	if (hit.bBlockingHit)
	{
		FVector GrapplePoint = hit.Location;
		//GrappleAxis = CalculateGrappleAxis(traceDirection.Vector());
		FVector GrappleAxis = GetActorRightVector() * -1;

		// Pass grapple data to movement component
		MovementComponent->SetGrapple(GrapplePoint, GrappleAxis, hit.Distance);

		// Set movement mode to swinging (will call GrapplePhysCustom() to handle movement)
		MovementComponent->SetMovementMode(EMovementMode::MOVE_Custom, static_cast<int>(ECustomMovementType::Swing));
	}

	return hit;
}

// Called to bind functionality to input
void AGrappleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

