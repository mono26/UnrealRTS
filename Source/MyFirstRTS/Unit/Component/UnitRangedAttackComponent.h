// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UnitAttackComponent.h"
#include "../../Projectile/RTSProjectile.h"
#include "UnitRangedAttackComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UUnitRangedAttackComponent : public UUnitAttackComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RangedAttack")
	USceneComponent* Muzzle;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ARTSProjectile> ProjectileClass;

public:
	virtual void ExecuteAttack() override;

	virtual void OnExecuteAttack() override;
};
