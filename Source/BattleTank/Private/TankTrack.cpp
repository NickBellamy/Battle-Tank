// Copyright Nick Bellamy.

#include "TankTrack.h"

// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	// Registers the OnHit() method
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate the speed of the tank velocity in the right direction
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	
	// Work out the required acceleration this frame to correct
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());
	
	// Calculate and apply in sideways direction for (F = ma)
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration;

	// Apply the CorrectionForce to the tank track
	TankRoot->AddForce(CorrectionForce / 2);	// Divide by two as there are two tracks

}

// Called from the Engine whenever there is a collision with the tank track
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
					   UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision from: %s"), *GetName());
}

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