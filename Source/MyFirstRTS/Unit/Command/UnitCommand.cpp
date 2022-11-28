// Copyright: For learning purposes, Mono Zubiria.


#include "UnitCommand.h"

UUnitCommand::UUnitCommand() : UObject()
{
	this->UnitRef = nullptr;
}

void UUnitCommand::SetUnit(AActor* Unit)
{
	this->UnitRef = Unit;
}

void UUnitCommand::SetOnSuccess(FActionSignature Callback)
{
	this->OnSuccess = Callback;
}

void UUnitCommand::SetOnFail(FActionSignature Callback)
{
	this->OnFail = Callback;
}

void UUnitCommand::Execute()
{
}