// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitCommand.generated.h"

/* https://benui.ca/unreal/delegates-advanced/#events */
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
	void SetOnSuccess(FActionSignature Callback);
	void SetOnFail(FActionSignature Callback);
};
