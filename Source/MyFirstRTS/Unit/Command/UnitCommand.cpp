// Copyright: For learning purposes, Mono Zubiria.


#include "UnitCommand.h"

UUnitCommand::UUnitCommand() : UObject()
{
	this->UnitRef = nullptr;
	this->OnSuccess = FOnCommandUpdateSignature();
	this->OnFail = FOnCommandUpdateSignature();
}

void UUnitCommand::SetUnitRef(AActor* Unit)
{
	this->UnitRef = Unit;
}

void UUnitCommand::SetOnCommandSuccess(FOnCommandUpdateSignature Callback)
{
	this->OnSuccess = Callback;
}

void UUnitCommand::SetOnCommandFail(FOnCommandUpdateSignature Callback)
{
	this->OnFail = Callback;
}

void UUnitCommand::Execute()
{
}