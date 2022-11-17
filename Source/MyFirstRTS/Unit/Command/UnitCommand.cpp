// Copyright: For learning purposes, Mono Zubiria.


#include "UnitCommand.h"

UUnitCommand::UUnitCommand()
{
	this->UnitRef = nullptr;
}

UUnitCommand::UUnitCommand(AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail)
{
	this->UnitRef = UnitRef;
	this->OnSuccess = OnSuccess;
	this->OnFail = OnFail;
}

void UUnitCommand::Execute()
{
}