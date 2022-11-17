// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"
#include "UnitCommand.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UUnitCommand : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE(FOnCommandUpdateSignature);

protected:
	AActor* UnitRef;
	FOnCommandUpdateSignature OnSuccess;
	FOnCommandUpdateSignature OnFail;

public:
	UUnitCommand();
	UUnitCommand(AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail);

protected:
	virtual void Execute();
};
