// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	
};
