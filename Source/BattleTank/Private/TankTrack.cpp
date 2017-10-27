// Copyright Nick Bellamy.

#include "TankTrack.h"

// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate the speed of the tank velocity in the right direction
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	
	// Work out the required acceleration this frame to correct
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());
	
	// Calculate and apply in sideways direction for (F = ma)
	UPrimitiveComponent* TankRoot = (GetOwner()->GetRootPrimitiveComponent());	// TODO Question: https://community.gamedev.tv/t/why-does-getroot-return-a-uscenecomponent/46684
	FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration;

	// Apply the CorrectionForce to the tank track
	TankRoot->AddForce(CorrectionForce / 2);	// Divide by two as there are two tracks

}

void UTankTrack::SetThrottle(float Throttle)
{
	// Setup parameters for AddForceAtLocation
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	// Get tank body and cast it to UPrimitiveComponent so AddForceAtLocation can be called
	UPrimitiveComponent* TankRoot = (GetOwner()->GetRootPrimitiveComponent());	// TODO Question: https://community.gamedev.tv/t/why-does-getroot-return-a-uscenecomponent/46684

	// Applies force on the tank body at the location of the track
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}