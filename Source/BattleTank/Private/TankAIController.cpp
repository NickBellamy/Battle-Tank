// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		// TODO Move towards the player

		// Aim at the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// TODO Fire at the player if ready
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player Tank not found in TankAIController!"));
	}

}