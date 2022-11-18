// Copyright: For learning purposes, Mono Zubiria.


#include "PlayerCommander.h"

UMovementCommand* APlayerCommander::CreateMovementCommand(FVector TargetPosition, AActor* UnitRef, UUnitCommand::FOnCommandUpdateSignature OnSuccess, UUnitCommand::FOnCommandUpdateSignature OnFail)
{
	UMovementCommand movementCommmand = UMovementCommand(TargetPosition, UnitRef, OnSuccess, OnFail);
	return &movementCommmand;
}
