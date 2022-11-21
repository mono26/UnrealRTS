// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Unit/Command/UnitCommand.h"
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
	void ExecuteAttackCommand(AActor* Target, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	void ExecuteGatherCommand(AActor* Resource, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	void ExecuteMovementCommand(FVector TargetPosition, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	void ExecuteStopCommand(AActor* UnitRef);
};
