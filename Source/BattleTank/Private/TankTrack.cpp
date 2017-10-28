// Copyright Nick Bellamy.

#include "TankTrack.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	// Registers the OnHit() method
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

// Called from the Engine whenever the ground is in contact with the tank track
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
					   UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();

	// Apply corrective force to prevent the tank "slipping" sideways
	ApplySidewaysForce();

	// Reset Throttle
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);

}

void UTankTrack::DriveTrack()
{
	// Setup parameters for AddForceAtLocation
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	// Get tank body and cast it to UPrimitiveComponent so AddForceAtLocation can be called
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	// Applies force on the tank body at the location of the track
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate the speed of the tank velocity in the right direction
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Work out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetTimeSeconds();
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());

	// Calculate and apply in sideways direction for (F = ma)
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration;

	// Apply the CorrectionForce to the tank track
	TankRoot->AddForce(CorrectionForce / 2);	// Divide by two as there are two tracks

}