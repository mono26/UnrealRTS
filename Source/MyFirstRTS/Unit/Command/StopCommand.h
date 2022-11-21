// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UnitCommand.h"
#include "StopCommand.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UStopCommand : public UUnitCommand
{
	GENERATED_BODY()

public:
	UStopCommand();
	
protected:
	void Execute() override;
};
