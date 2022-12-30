// Copyright: For learning purposes, Mono Zubiria.


#include "RTSProjectile.h"
#include "../Unit/RTSUnit.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARTSProjectile::ARTSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARTSProjectile::BeginPlay()
{
	Super::BeginPlay();

    // ...
    USphereComponent* collisionComponent = this->FindComponentByClass<USphereComponent>();
    collisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

    this->MovementComponent = this->FindComponentByClass<URTSProjectileMovementComponent>();
}

// Called every frame
void ARTSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // ...
}

bool ARTSProjectile::IsInDamageRange(AActor* ActorToDamage)
{
    if (ActorToDamage == nullptr) {
        return false;
    }

    float sqrDistance = FVector::DistSquared(this->GetOwner()->GetActorLocation(), ActorToDamage->GetActorLocation());

    return sqrDistance <= 0.1f;
}

void ARTSProjectile::FireProjectile(FVector StartPoint, FVector EndPoint)
{
    if (this->MovementComponent == nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("Projectile is missing movement component."));
        return;
    }

    this->MovementComponent->SetStartPoint(StartPoint);
    this->MovementComponent->SetEndPoint(EndPoint);
    this->MovementComponent->StartMovement(true);
}

void ARTSProjectile::DealDamage(float DamageAmount, TArray<AActor*> ActorsToDamage)
{
    if (ActorsToDamage.IsEmpty()) {
        return;
    }

    ARTSUnit* asUnit = Cast<ARTSUnit>(this->ProjectileCreator);
    for (AActor* actorToDamage : ActorsToDamage) {
        if (!this->IsInDamageRange(actorToDamage)) {
            continue;
        }

        UGameplayStatics::ApplyDamage(actorToDamage, DamageAmount, asUnit->GetController(), asUnit, nullptr);
    }
}

void ARTSProjectile::SetProjectileCreator(AActor* Creator)
{
    this->ProjectileCreator = Creator;
}

void ARTSProjectile::SetOnImpact(FProjectileActionSignature Callback)
{
    this->OnImpact = Callback;
}

void ARTSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    // If the projectile hits it's owner do nothing.
    if (this->Owner == OtherActor) {
        UE_LOG(LogTemp, Warning, TEXT("Hit it's own creator."));
        return;
    }

    this->MovementComponent->StartMovement(false);

    this->OnImpact.ExecuteIfBound(this);

    this->Destroy();
}
