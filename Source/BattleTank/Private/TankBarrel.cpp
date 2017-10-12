// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) const
{
	// Diagnostic Log
	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called at speed: %f"), RelativeSpeed);

	// TODO Move the barrel the right amount this frame given a max elevation speed, and the frame time


}