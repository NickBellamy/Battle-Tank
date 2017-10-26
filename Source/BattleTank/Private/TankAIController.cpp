// Copyright Nick Bellamy.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
// Depends on movement component via pathfinding system


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* ControlledTank = GetPawn();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);	// TODO Check AcceptanceRadius is sensible

		// Aim at the player
		UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		AimingComponent->Fire();		// TODO Fire at the player if ready
	}

}