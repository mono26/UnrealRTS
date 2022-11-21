// Copyright: For learning purposes, Mono Zubiria.


#include "GatherCommand.h"
#include "../WorkerUnit.h"
#include "MovementCommand.h"

UGatherCommand::UGatherCommand()
{
	this->ResourceRef = nullptr;

	this->OnReachResourceDelegate.BindUFunction(this, FName("OnReachResource"));
	this->OnReachResourceFailDelegate.BindUFunction(this, FName("OnReachResourceFail"));
}

void UGatherCommand::Execute()
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

	// TODO move to target
	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnitRef(this->UnitRef);
	movementCommmand->SetTargetPosition(this->ResourceRef->GetActorLocation());
	movementCommmand->SetOnCommandSuccess(this->OnReachResourceDelegate);
	movementCommmand->SetOnCommandFail(this->OnReachResourceFailDelegate);
	asWorker->ExecuteCommand(movementCommmand);
	// TODO extract resource
}

void UGatherCommand::SetResourceRef(AActor* Resource)
{
	this->ResourceRef = Resource;
}

void UGatherCommand::OnReachResource()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReachResource"));
}

void UGatherCommand::OnReachResourceFail()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReachResourceFail"));

	this->OnFail.ExecuteIfBound();
}
