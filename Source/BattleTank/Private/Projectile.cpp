// Copyright Nick Bellamy.

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);					// Sets CollisionMesh as the root component in the Projectile BP
	CollisionMesh->SetNotifyRigidBodyCollision(true);	// Turn on collision notification
	CollisionMesh->SetVisibility(false);				// Turns off visibility of projectiles; will be relying on particle effects

	LaunchBlast = CreateDefaultSubobject <UParticleSystemComponent>(FName("Launch Blast"));
	// TODO Should SetupAttachment() be used instead as it is called in the Constructor?
	// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/USceneComponent/SetupAttachment/index.html
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject <UParticleSystemComponent>(FName("Impact Blast"));
	// TODO Should SetupAttachment() be used instead as it is called in the Constructor?
	// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/USceneComponent/SetupAttachment/index.html
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;					// Prevent impact blast particle effect triggering on initialization

	ExplosionForce = CreateDefaultSubobject <URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;			// Prevent projectile firing on initialization

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed) const
{
	// No need to protect pointer as it's added at construction

	// ForwardVector is the correct orientation as on initialization of the projectile 
	// in Tank::Fire(), the rotation is set to be the same as the tank barrel's rotation
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);

	// Reactivate the ProjectileMovementComponent that was deactivated in the Projectile constructor
	ProjectileMovement->Activate();

}

// Called from the Engine whenever the projectile hits another object
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
}