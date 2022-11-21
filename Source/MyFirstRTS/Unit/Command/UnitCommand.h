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
	virtual void Execute();

public: 
	void SetUnitRef(AActor* Unit);
	void SetOnCommandSuccess(FOnCommandUpdateSignature Callback);
	void SetOnCommandFail(FOnCommandUpdateSignature Callback);
};
