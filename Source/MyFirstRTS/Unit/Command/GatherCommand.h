// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "UnitCommand.h"
#include "GatherCommand.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UGatherCommand : public UUnitCommand
{
	GENERATED_BODY()
	
protected:
	AActor* ResourceRef;

	FOnCommandUpdateSignature OnReachResourceDelegate;
	FOnCommandUpdateSignature OnReachResourceFailDelegate;

public:
	UGatherCommand();

public:
	void Execute() override;

public:
	void SetResource(AActor* Resource);

	UFUNCTION()
	void OnReachResource();
	UFUNCTION()
	void OnReachResourceFail();
};
