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
	AActor* AttackTargetRef;

	FOnCommandUpdateSignature OnReachAttackTargetDelegate;
	FOnCommandUpdateSignature OnReachAttackTargetFailDelegate;

public:
	UAttackCommand();

public:
	void Execute() override;

public:
	void SetTargetRef(AActor* Target);

	void OnReachAttackTarget();
	void OnReachAttackTargetFail();
};
