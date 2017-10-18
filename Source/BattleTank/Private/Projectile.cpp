// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"	// Only needed for GetWorld() in diagnostic log
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// No need to protect pointer as it's added at construction
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));

	// Prevent projectile firing on initialization
	ProjectileMovement->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed) const
{
	// Diagnostic log
	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f Projectile Launched at %fm/s!"), Time, Speed);

	// ForwardVector is the correct orientation as on initialization of the projectile 
	// in Tank::Fire(), the rotation is set to be the same as the tank barrel's rotation
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);

	// Reactivate the ProjectileMovementComponent that was deactivated in the Projectile constructor
	ProjectileMovement->Activate();

}