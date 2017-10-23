// Copyright Nick Bellamy.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

// This function call is triggered by the MoveToActor() call in the TankAIController
// It is overridden to allow the MoveVelocity to be passed into our custom control system
// which can then be utilised by the AI
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we are completely overriding this function

	FVector TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForwardDirection, AIForwardIntention));
	IntendTurnRight(FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	// Pointer protection
	if (!LeftTrack || !RightTrack) { return; }

	// TODO Clamp the Throw value between +1 and -0.5
	
	// TODO Prevent double speed due to dual control setup
	// Pushing forward on the left stick and holding both shoulder buttons down simultaneously
	// makes the tank go twice as fast as it should

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	// Pointer protection
	if (!LeftTrack || !RightTrack) { return; }

	// TODO Prevent double speed due to dual control setup

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}