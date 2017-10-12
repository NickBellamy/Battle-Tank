// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"	// Only needed for GetWorld() to output time in diagnostic log

void UTankBarrel::Elevate(float RelativeSpeed) const
{
	// Diagnostic Log
	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f Barrel->Elevate() called at speed: %f"), Time, RelativeSpeed);

	// TODO Move the barrel the right amount this frame given a max elevation speed, and the frame time


}