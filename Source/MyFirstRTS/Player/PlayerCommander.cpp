// Copyright: For learning purposes, Mono Zubiria.


#include "PlayerCommander.h"
#include "../Unit/Command/MovementCommand.h"
#include "../Unit/Command/StopCommand.h"

void APlayerCommander::ExecuteMovementCommand(FVector TargetPosition, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail)
{
	if (UnitRef == nullptr) {
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnitRef(UnitRef);
	movementCommmand->SetTargetPosition(TargetPosition);
	movementCommmand->SetOnCommandSuccess(OnSuccess);
	movementCommmand->SetOnCommandFail(OnFail);
	asWorker->ExecuteCommand(movementCommmand);
}

void APlayerCommander::ExecuteStopCommand(AActor* UnitRef)
{
	if (UnitRef == nullptr) {
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UStopCommand* stopCommand = NewObject<UStopCommand>();
	stopCommand->SetUnitRef(UnitRef);
	asWorker->ExecuteCommand(stopCommand);
}
