// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Setter method
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Function to make tank aim at a location, delegated from Tank class
	void AimAt(FVector HitLocation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	// Barrel component of the Tank
	UStaticMeshComponent* Barrel = nullptr;
};