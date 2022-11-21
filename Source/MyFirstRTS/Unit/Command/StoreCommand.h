// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GatherCommand.h"
#include "StoreCommand.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API UStoreCommand : public UGatherCommand
{
	GENERATED_BODY()
	
protected:
	AActor* StorageRef;

public:
	UStoreCommand();

public:
	void Execute() override;

public:
	void SetStorage(AActor* Storage);
};
