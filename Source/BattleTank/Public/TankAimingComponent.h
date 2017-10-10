// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// TODO Forward declaration implemented for demonstration puposes
//		Replace with #include to TankBarrel.h at a later date?
//		Seems best practice to try to avoid forward declarations
//		where possible:
//		https://google.github.io/styleguide/cppguide.html#Forward_Declarations
class UTankBarrel;

// Holds barrel's properties and methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Setter method
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// TODO Add set turret reference

	// Function to make tank aim at a location, delegated from Tank class
	void AimAt(FVector HitLocation, float LaunchSpeed);
	
private:
	// Barrel component of the Tank
	UTankBarrel* Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDireciton) const;
};
