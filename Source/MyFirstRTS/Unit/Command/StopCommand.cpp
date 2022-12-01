// Copyright: For learning purposes, Mono Zubiria.


#include "StopCommand.h"
#include "../WorkerUnit.h"

UStopCommand::UStopCommand() : Super()
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

	UE_LOG(LogTemp, Warning, TEXT("ExecuteStopCommand"));

	asWorker->StopAllActions();

	this->OnSuccess.ExecuteIfBound();
}

