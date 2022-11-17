// Copyright: For learning purposes, Mono Zubiria.

#include "MovementCommand.h"
#include "UnitCommand.h"

UMovementCommand::UMovementCommand() : UUnitCommand()
{
}

UMovementCommand::UMovementCommand(AActor* UnitRef, FVector TargetPosition) : UUnitCommand(UnitRef)
{
	this->TargetPosition = TargetPosition;
}

void UMovementCommand::Execute()
{
	if (this->UnitRef == nullptr) {
		return;
	}


}
