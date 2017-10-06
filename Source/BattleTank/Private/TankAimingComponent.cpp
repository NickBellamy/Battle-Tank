// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;

}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	// Diagnostic log of HitLocation and BarrelLocation
	if (Barrel)
	{
		FString TankName = GetOwner()->GetName();
		FVector BarrelLocation = Barrel->GetComponentLocation();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s from: %s"), *TankName, *HitLocation.ToString(), *BarrelLocation.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel not found from class %s"), *this->GetClass()->GetName());
	}

	// TODO Make the tank aim at the HitLocation

}