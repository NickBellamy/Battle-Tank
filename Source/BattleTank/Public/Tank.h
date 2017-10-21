// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankAimingComponent;
class UTankBarrel;
class UTankMovementComponent;
class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called in the Tank Blueprint BeginPlay method
	// Allows this to be soft coded rather than hard coded in C++
	UFUNCTION(BLueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Called in the Tank Blueprint BeginPlay method
	// Allows this to be soft coded rather than hard coded in C++
	UFUNCTION(BLueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BLueprintCallable)
		void Fire();

	// Tells the tank where to aim
	void AimAt(FVector HitLocation) const;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Local barrel for spawning projectiles
	UTankBarrel* Barrel = nullptr;

	// Used to determine firing intervals, simulating reload time
	double LastFireTime = 0;

};