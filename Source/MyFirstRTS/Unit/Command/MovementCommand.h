// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UnitCommand.h"
#include "../WorkerUnit.h"
#include "MovementCommand.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UMovementCommand : public UUnitCommand
{
	GENERATED_BODY()
	
protected:
	FVector TargetPosition;

	AWorkerUnit::FOnMovementUpdateSignature OnReachedPositionDelegate;
	AWorkerUnit::FOnMovementUpdateSignature OnReachPositionFailDelegate;

public:
	UMovementCommand();

public:
	void Execute() override;

public:
	void SetTargetPosition(FVector Position);

	void OnReachedTargetPosition();
	void OnReachTargetPositionFail();
};
