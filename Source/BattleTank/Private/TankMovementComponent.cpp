// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

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