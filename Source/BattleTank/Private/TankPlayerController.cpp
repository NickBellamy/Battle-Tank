// Copyright Nick Bellamy.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}

}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Tank Died"));
	// TODO Call spectator mode
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair() const
{
	// Pointer protection needed here to prevent a bug that results in UE Editor crashing
	// when PlayerController_BP is opened.  The bug causes the ATankPlayerController::Tick()
	// event to fire on opening the blueprint, which then calls AimTowardsCrosshair().
	// Because there is no Pawn constructed when opening the Blueprint, GetPawn() returns a
	// nullptr, which causes the crash.  https://issues.unrealengine.com/issue/UE-36929
	if (!(GetPawn())) { return; }

	// TODO AimingComponent set on every tick; is this warranted?
	// If not, could the AimingComponent set in BeginPlay() be used instead?
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;

	// TODO Look at implementing GetHitResultAtScreenPosition() for a more elegant solution
	// See here: https://community.gamedev.tv/t/unreal-provides-a-much-simpler-way-to-accomplish-all-of-this/2557
	// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/APlayerController/GetHitResultAtScreenPosition/1/index.html
	if (GetSightRayHitLocation(HitLocation))
	{		
		// Tell controlled tank to aim at this point
		AimingComponent->AimAt(HitLocation);
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
		// Returns true if we hit something
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;

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
	HitLocation = FVector(0);	// Prevents seemingly random values being returned on "miss"
	return false;
}