// Copyright Nick Bellamy.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding system

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}

}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* ControlledTank = GetPawn();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	// PlayerTank not ensured as this condition triggers when player dies and goes into spectator mode
	if (!PlayerTank || !ensure(ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim at the player
	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// if locked
	if(AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}				

}