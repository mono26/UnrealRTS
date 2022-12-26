// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYFIRSTRTS_API IUnitComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void StopAction();
};
