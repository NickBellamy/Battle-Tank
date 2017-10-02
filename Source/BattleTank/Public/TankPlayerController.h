// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)	
		float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere) 
		float CrosshairYLocation = 0.333333f;

	// Get the tank that the player controller is possessing
	ATank* GetControlledTank() const;

	// Move the barrel to point to where the crosshair intersects with the world
	void AimTowardsCrosshair();

	// Return OUT parameter, true if hit landscape	
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

};