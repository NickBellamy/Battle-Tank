// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	// Diagnostic log
	UE_LOG(LogTemp, Warning, TEXT("Intend to move forward throw: %f"), Throw);

	// TODO Clamp the Throw value between +1 and -0.5
}