// Copyright Nick Bellamy.

#include "TankBarrel.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// RelativeSpeed sould always be between -1 and +1
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// Move the barrel the right amount this frame given a max elevation speed, and the frame time
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

}