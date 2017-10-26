// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000000;	// Unrealistic force, but necessary for the way in which movement is setup

	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	
};