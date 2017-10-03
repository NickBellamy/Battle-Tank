// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController not possessing a Tank Pawn!"));
	}
	else
	{
		// TODO Remove this log - diagnostic only output
		UE_LOG(LogTemp, Warning, TEXT("Tank Pawn found. Name is: %s"), *(ControlledTank->GetName()));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
		
		// TODO Tell controlled tank to aim at this point
	}

}

// Get world location of linetrace through crosshair
// Returns true if hits anywhere but Sky Box
// Updates HitLocation with the location to hit
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(CrosshairLocation, LookDirection))
	{
		// Line trace along that look direction, and see what we hit (up to maximum range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;	// TODO Only return true if landscape is hit by Raycast

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;	// Not used; only needed for DeprojectScreenPositionToWorld parameter
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	// TODO Ensure line trace is correctly working
	// At the moment it appears to hit its own tank pawn when moving the camera low down
	// Possibly move the start position to be above the tank (instead of at the camera)
	// or make sure the tank pawn is passed through on the collision channel
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation,	ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);	// Prevent seemingly random values being returned on "miss"
	return false;
}