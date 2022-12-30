// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Unit/Command/UnitCommand.h"
#include "Component/RTSProjectileMovementComponent.h"
#include "RTSProjectile.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FProjectileActionSignature, ARTSProjectile*, Projectile);

UCLASS()
class MYFIRSTRTS_API ARTSProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	AActor* ProjectileCreator;

	URTSProjectileMovementComponent* MovementComponent;

public:
	FProjectileActionSignature OnImpact;

public:	
	// Sets default values for this actor's properties
	ARTSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool IsInDamageRange(AActor* ActorToDamage);

	// Function that is called when the projectile hits something.
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
	void FireProjectile(FVector StartPoint, FVector EndPoint);

	void DealDamage(float DamageAmount, TArray<AActor*> ActorsToDamage);

	void SetProjectileCreator(AActor* Creator);

	void SetOnImpact(FProjectileActionSignature Callback);
};
