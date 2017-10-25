// Copyright Nick Bellamy.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation) const
{
	if (!ensure(Barrel)) { return; }

	// Calculate the Launch Velocity and convert to unit vector if successful
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, 
													HitLocation, LaunchSpeed, false, 0.0f, 0.0f,
													// TODO Is DoNotTrace the correct parameter?
													// Asked for clarification here:
													// https://community.gamedev.tv/t/whats-the-difference-between-the-parameter-types/45040
													ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		// Convert to unit vector to get direction of launch
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelAndTurretTowards(AimDirection);
	}
	
	// No aiming solution found if execution reaches this line
	
}

void UTankAimingComponent::MoveBarrelAndTurretTowards(FVector AimDirection) const
{
	// Pointer protection
	if (!ensure(Barrel && Turret)) { return; }

	// Calculate the delta between the current, and desired barrel rotation
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);	// Elevate barrel
	Turret->Rotate(DeltaRotator.Yaw);		// Rotate Turret
}