// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;

// Holds barrel's & turret's properties and methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Setter method
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Setter method
	void SetTurretReference(UTankTurret* TurretToSet);

	// Function to make tank aim at a location, delegated from Tank class
	void AimAt(FVector HitLocation, float LaunchSpeed) const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringStatus = EFiringState::Aiming;
	
private:
	// Barrel component of the Tank
	UTankBarrel* Barrel = nullptr;

	// Turret component of the Tank
	UTankTurret* Turret = nullptr;

	void MoveBarrelAndTurretTowards(FVector AimDireciton) const;

};