// Copyright: For learning purposes, Mono Zubiria.


#include "StopCommand.h"
#include "../WorkerUnit.h"

UStopCommand::UStopCommand() : Super()
{
}

void UStopCommand::Execute()
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteStopCommand"));

	asWorker->StopAllActions();
}

