// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UnitCommand.h"
#include "AttackCommand.generated.h"

/**
 *
 */
UCLASS()
class MYFIRSTRTS_API UAttackCommand : public UUnitCommand
{
	GENERATED_BODY()

protected:
	AActor* AttackTarget;

	FActionSignature OnReachAttackTargetDelegate;

public:
	UAttackCommand();

public:
	void Execute() override;

public:
	void SetAttackTarget(AActor* Target);

	UFUNCTION()
	void OnReachAttackTarget();
};
