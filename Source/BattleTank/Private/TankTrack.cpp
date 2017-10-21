// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// Setup parameters for AddForceAtLocation
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	// Get tank body and cast it to UPrimitiveComponent so AddForceAtLocation can be called
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	// Applies force on the tank body at the location of the track
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}