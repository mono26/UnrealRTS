// Copyright: For learning purposes, Mono Zubiria.


#include "RTSProjectile.h"

// Sets default values
ARTSProjectile::ARTSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARTSProjectile::BeginPlay()
{
    UE_LOG(LogTemp, Warning, TEXT("Projectile BeginPlay"));

	Super::BeginPlay();

	this->CollisionComponent = this->FindComponentByClass<USphereComponent>();
    this->CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

    this->ProjectileMovementComponent = this->FindComponentByClass<UProjectileMovementComponent>();
    this->ProjectileMovementComponent->SetUpdatedComponent(this->CollisionComponent);
    this->ProjectileMovementComponent->InitialSpeed = 3000.0f;
    this->ProjectileMovementComponent->MaxSpeed = 3000.0f;
    this->ProjectileMovementComponent->bRotationFollowsVelocity = true;
    this->ProjectileMovementComponent->bShouldBounce = false;
    // this->ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

// Called every frame
void ARTSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARTSProjectile::FireInDirection(const FVector& ShootDirection)
{
    this->ProjectileMovementComponent->Velocity = ShootDirection * this->ProjectileMovementComponent->InitialSpeed;
}

void ARTSProjectile::SetOnImpact(FActionSignature Callback)
{
    this->OnImpact = Callback;
}

// Function that is called when the projectile hits something.
void ARTSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("OnHit"));

    this->OnImpact.ExecuteIfBound();

    if (OtherActor != this && OtherComponent->IsSimulatingPhysics()) {
        OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    }

    this->Destroy();
}
