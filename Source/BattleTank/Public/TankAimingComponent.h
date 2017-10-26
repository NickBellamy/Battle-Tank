// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class AProjectile;
class UTankBarrel;
class UTankTurret;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Holds barrel's & turret's properties and methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Setter method
	UFUNCTION(BLueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Function to make tank aim at a location, delegated from Tank class
	void AimAt(FVector HitLocation) const;

	UFUNCTION(BLueprintCallable)
		void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringStatus = EFiringState::Aiming;
	
private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Barrel component of the Tank
	UTankBarrel* Barrel = nullptr;

	// Turret component of the Tank
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	// Used to determine firing intervals, simulating reload time
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	void MoveBarrelAndTurretTowards(FVector AimDireciton) const;

};