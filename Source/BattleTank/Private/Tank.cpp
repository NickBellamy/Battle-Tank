// Copyright Nick Bellamy.

#include "Tank.h"

// Sets default values for this component's properties
ATank::ATank()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	// CurrentHealth set here to allow consideration of any changes to the value set in the blueprint.
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount,	struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	// Creates int version of DamageAmount because when clamping, we don't want floats of 0
	// being compared with other floats of 0 as rounding errors can occur, altering the logic
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		// Broadcasts OnDeath that will be picked up by listener functions
		OnDeath.Broadcast();
	}
	return DamageToApply;

}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;	// Cast as floats because values are of type int32
}
