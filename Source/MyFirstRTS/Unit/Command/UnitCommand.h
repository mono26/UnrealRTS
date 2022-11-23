// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitCommand.generated.h"

DECLARE_DYNAMIC_DELEGATE(FActionSignature);

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UUnitCommand : public UObject
{
	GENERATED_BODY()

protected:
	AActor* UnitRef;
	// TODO use events instead.
	FActionSignature OnSuccess;
	FActionSignature OnFail;

public:
	UUnitCommand();

public:
	virtual void Execute();

public: 
	void SetUnit(AActor* Unit);
	void SetOnCommandSuccess(FActionSignature Callback);
	void SetOnCommandFail(FActionSignature Callback);
};
