// Copyright: For learning purposes, Mono Zubiria.


#include "UnitCommand.h"

UUnitCommand::UUnitCommand() : UObject()
{
	this->UnitRef = nullptr;
}

void UUnitCommand::SetUnitRef(AActor* UnitRef)
{
	this->UnitRef = UnitRef;
}

void UUnitCommand::SetOnCommandSuccess(FOnCommandUpdateSignature OnSuccess)
{
	this->OnSuccess = OnSuccess;
}

void UUnitCommand::SetOnCommandFail(FOnCommandUpdateSignature OnFail)
{
	this->OnFail = OnFail;
}

void UUnitCommand::Execute()
{
}