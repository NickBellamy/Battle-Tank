// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sets an event that can be triggered and leveraged in blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	UPROPERTY(EditDefaultsOnly)	
		float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.333333f;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;

	// Move the barrel of the tank to point to where the crosshair intersects with the world
	void AimTowardsCrosshair();

	// Returns true if look direction can be determined
	// Sets out parameter LookDireciton to a unit vector of that direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	// Returns true if blocking hit is found
	// Sets out parameter HitLocation to the point in 3D space that would be hit
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	// Return OUT parameter, true if hit landscape	
	bool GetSightRayHitLocation(FVector& HitLocation) const;

};