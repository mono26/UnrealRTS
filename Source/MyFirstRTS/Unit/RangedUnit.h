// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "RTSUnit.h"
#include "RangedUnit.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API ARangedUnit : public ARTSUnit
{
	GENERATED_BODY()
	
public:

	virtual void StopAllActions() override;
};
