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

public:

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = "RangedAttack")
	TSubclassOf<class ARTSProjectile> ProjectileClass;

private:
	FActionSignature OnImpactDelegate;

public:
	UUnitRangedAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void ExecuteAttack() override;

	virtual void OnExecuteAttack() override;

	void OnImpact();
};
