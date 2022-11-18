// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Unit/Command/UnitCommand.h"
#include "../Unit/Command/MovementCommand.h"
#include "PlayerCommander.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API APlayerCommander : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	UMovementCommand* CreateMovementCommand(FVector TargetPosition, AActor* UnitRef, UUnitCommand::FOnCommandUpdateSignature OnSuccess, UUnitCommand::FOnCommandUpdateSignature OnFail);
};
