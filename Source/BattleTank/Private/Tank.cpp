// Copyright Nick Bellamy.

#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Directs the tank where to aim
void ATank::AimAt(FVector HitLocation) const
{
	// Pointer protection
	if (!TankAimingComponent) { return; }

	// Delegate Aiming to TankAimingComponent
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

}

void ATank::Fire()
{
	// Pointer protection
	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel not found from class %s"), *this->GetClass()->GetName());
		return;
	}

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	if (isReloaded)
	{
		// Spawn a projectile at the socket location on the barrel
		FName SocketName = FName("Projectile");
		FVector SocketLocation = Barrel->GetSocketLocation(SocketName);
		FRotator SocketRotation = Barrel->GetSocketRotation(SocketName);
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	} 

}