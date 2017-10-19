// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "UObject/UObjectBaseUtility.h"		// Only needed for the GetName() in the diagnostic log in SetThrottle()

void UTankTrack::SetThrottle(float Throttle)
{
	// Diagnostic log
	FString Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

	//TODO Clamp throttle value between -1 and +1 so player can't overdrive

}