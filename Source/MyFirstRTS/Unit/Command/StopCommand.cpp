// Copyright: For learning purposes, Mono Zubiria.


#include "StopCommand.h"
#include "../RTSUnit.h"

UStopCommand::UStopCommand() : Super()
{
}

void UStopCommand::Execute()
{
	ARTSUnit* asWorker = Cast<ARTSUnit>(this->UnitRef);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteStopCommand"));

	asWorker->StopAllActions();
}

