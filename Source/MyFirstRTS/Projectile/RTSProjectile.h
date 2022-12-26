// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Unit/Command/UnitCommand.h"
#include "RTSProjectile.generated.h"

UCLASS()
class MYFIRSTRTS_API ARTSProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	FActionSignature OnImpact;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

public:	
	// Sets default values for this actor's properties
	ARTSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

public:
	void SetOnImpact(FActionSignature Callback);

	// Function that is called when the projectile hits something.
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
