// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

/// I'm not certain which header file to reference to enable GetWorld() to be called.
/// Asked question in forums:
/// https://community.gamedev.tv/t/which-reference-to-getworld-should-we-be-using/43910
/// https://answers.unrealengine.com/questions/711371/why-is-getworld-defined-in-three-seperate-places.html
/// Decided on "Engine/World.h" for now as it makes the most sense to me syntactically
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController can't find player tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player Tank called: %s"), *(PlayerTank->GetName()));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		// TODO Move towards the player

		// Aim at the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// TODO Fire at the player if ready
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player Tank not found in TankAIController!"));
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

}