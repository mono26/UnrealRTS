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
	FVector TargetPosition;

public:
	UMovementCommand();
	UMovementCommand(AActor* UnitRef, FVector Position);

protected:
	void Execute() override;
};
