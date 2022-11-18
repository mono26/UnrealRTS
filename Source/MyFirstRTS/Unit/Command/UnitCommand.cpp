// Copyright: For learning purposes, Mono Zubiria.


#include "UnitCommand.h"

UUnitCommand::UUnitCommand() : UUnitCommand(nullptr, FOnCommandUpdateSignature(), FOnCommandUpdateSignature())
{

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