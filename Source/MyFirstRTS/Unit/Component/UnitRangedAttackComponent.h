// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UnitAttackComponent.h"
#include "../../Projectile/RTSProjectile.h"
#include "../../Component/WeaponSocketComponent.h"
#include "UnitRangedAttackComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UUnitRangedAttackComponent : public UUnitAttackComponent
{
	GENERATED_BODY()
	
private:
	UWeaponSocketComponent* Muzzle;

protected:
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = "RangedAttack")
	TSubclassOf<class ARTSProjectile> ProjectileClass;

private:
	FProjectileActionSignature OnImpactDelegate;

public:
	UUnitRangedAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	ARTSProjectile* CreateProjectile();

	UFUNCTION()
	void OnImpact(ARTSProjectile* Projectile);

protected:
	virtual void OnExecuteAttack() override;

public:
	virtual void ExecuteAttack() override;
};
