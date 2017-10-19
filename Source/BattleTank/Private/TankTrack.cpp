// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "UObject/UObjectBaseUtility.h"		// Only needed for the GetName() in the diagnostic log in SetThrottle()

void UTankTrack::SetThrottle(float Throttle)
{
	// Diagnostic log
	FString Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

	//TODO Clamp throttle value between -1 and +1 so player can't overdrive

	// Setup parameters for AddForceAtLocation
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	// Get tank body and cast it to UPrimitiveComponent so AddForceAtLocation can be called
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	// Applies force on the tank body at the location of the track
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}