// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"
#include "UnitCommand.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnCommandUpdateSignature);

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UUnitCommand : public UObject
{
	GENERATED_BODY()

protected:
	AActor* UnitRef;
	FOnCommandUpdateSignature OnSuccess;
	FOnCommandUpdateSignature OnFail;

public:
	UUnitCommand();

public:
	void SetUnitRef(AActor* UnitRef);
	void SetOnCommandSuccess(FOnCommandUpdateSignature OnSuccess);
	void SetOnCommandFail(FOnCommandUpdateSignature OnFail);

	virtual void Execute();
};
