// Copyright: For learning purposes, Mono Zubiria.


#include "StopCommand.h"
#include "../WorkerUnit.h"

UStopCommand::UStopCommand() : UUnitCommand()
{
}

void UStopCommand::Execute()
{
	if (this->UnitRef == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	asWorker->StopAllActions();

	this->OnSuccess.ExecuteIfBound();
}

