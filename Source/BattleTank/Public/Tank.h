// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Declares delegate function of type FTankDelegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ATank();

	// Called by the engine when AActor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Returns current health as a value between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")		// BlueprintPure is essentially "const" for Blueprints
		float GetHealthPercent() const;

	// Creates OnDeath of type FTankDelegate
	FTankDelegate OnDeath;

private:
	// Used in calculation of GetHealthPercent()
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth = StartingHealth;
};