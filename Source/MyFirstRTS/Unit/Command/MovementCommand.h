// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UnitCommand.h"
#include "MovementCommand.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UMovementCommand : public UUnitCommand
{
	GENERATED_BODY()
	
protected:
	float AcceptanceRange;
	FVector TargetPosition;

	FActionSignature OnReachedPositionDelegate;
	FActionSignature OnReachPositionFailDelegate;

public:
	UMovementCommand();

public:
	void Execute() override;

public:
	void SetAcceptanceRange(float Range);
	void SetTargetPosition(FVector Position);

	UFUNCTION()
	void OnReachTargetPosition();
	UFUNCTION()
	void OnReachTargetPositionFail();
};
