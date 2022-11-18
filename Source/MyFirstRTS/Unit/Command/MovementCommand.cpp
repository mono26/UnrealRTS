// Copyright: For learning purposes, Mono Zubiria.

#include "MovementCommand.h"
#include "../WorkerUnit.h"

UMovementCommand::UMovementCommand() : UMovementCommand(FVector::Zero(), nullptr, UUnitCommand::FOnCommandUpdateSignature(), UUnitCommand::FOnCommandUpdateSignature())
{
}

UMovementCommand::UMovementCommand(FVector TargetPosition, AActor* UnitRef, UUnitCommand::FOnCommandUpdateSignature OnSuccess, UUnitCommand::FOnCommandUpdateSignature OnFail) : UUnitCommand(UnitRef, OnSuccess, OnFail)
{
	this->TargetPosition = TargetPosition;

	this->OnReachedPositionDelegate.BindUFunction(this, FName("OnReachedTargetPosition"));
	this->OnFailToReachPositionDelegate.BindUFunction(this, FName("OnFailToReachTargetPosition"));
}

void UMovementCommand::Execute()
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

	asWorker->MoveToPosition(this->TargetPosition, this->OnReachedPositionDelegate, this->OnFailToReachPositionDelegate);
}

void UMovementCommand::OnReachedTargetPosition()
{
	this->OnSuccess.ExecuteIfBound();
}

void UMovementCommand::OnFailToReachTargetPosition()
{
	this->OnFail.ExecuteIfBound();
}
