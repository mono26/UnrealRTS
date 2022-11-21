// Copyright: For learning purposes, Mono Zubiria.

#include "MovementCommand.h"
#include "../WorkerUnit.h"

UMovementCommand::UMovementCommand() : UUnitCommand()
{
	this->TargetPosition = FVector::Zero();

	this->OnReachedPositionDelegate.BindUFunction(this, FName("OnReachedTargetPosition"));
	this->OnReachPositionFailDelegate.BindUFunction(this, FName("OnFailToReachTargetPosition"));
}

void UMovementCommand::SetTargetPosition(FVector Position)
{
	this->TargetPosition = Position;
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

	asWorker->MoveToPosition(this->TargetPosition, this->OnReachedPositionDelegate, this->OnReachPositionFailDelegate);
}

void UMovementCommand::OnReachedTargetPosition()
{
	this->OnSuccess.ExecuteIfBound();
}

void UMovementCommand::OnReachTargetPositionFail()
{
	this->OnFail.ExecuteIfBound();
}
