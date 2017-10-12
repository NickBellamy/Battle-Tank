// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	// TODO Should this really tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;

}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	// Pointer protection
	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel not found from class %s"), *this->GetClass()->GetName());
		return;
	}

	// Calculate the Launch Velocity and convert to unit vector if successful
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation,
													LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		// Convert to unit vector to get direction of launch
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const
{
	// Calculate the delta between the current, and desired barrel rotation
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionRotator - BarrelRotator;

	Barrel->Elevate(5);	// TODO Change passed value; 5.0 entered for testing purposes

}