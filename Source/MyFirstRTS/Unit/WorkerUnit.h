// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "Delegates/Delegate.h"
#include "RTSUnit.h"
#include "WorkerUnit.generated.h"

UCLASS()
class MYFIRSTRTS_API AWorkerUnit : public ARTSUnit
{
	GENERATED_BODY()

public:

	virtual void StopAllActions() override;
};
