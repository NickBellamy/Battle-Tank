// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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
		// TODO Tell controlled tank to aim at this point
	}

}

// Get world location of linetrace through crosshair, returns true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); 
	FVector2D CrosshairLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(CrosshairLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction is: %s"), *LookDirection.ToString());
	}

	// TODO Line trace along that look direction, and see what we hit (up to maximum range)

	OutHitLocation = FVector(1.0);	// TODO Raycast to get actual HitLocation
	return true;					// TODO Only return true if landscape is hit by Raycast

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;	// Not used; only needed for DeprojectScreenPositionToWorld parameter
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	

}