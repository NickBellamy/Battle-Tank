// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// RelativeSpeed sould always be between -1 and +1
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// Move the turret the right amount this frame given a max elevation speed, and the frame time
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotationChange;

	// TODO Currently this doesn't allow the turret to rotate past +180 and -180 degrees
	// Converting to quaternions may solve this issue!
	SetRelativeRotation(FRotator(0, Rotation, 0));

}