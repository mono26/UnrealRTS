// Copyright: For learning purposes, Mono Zubiria.


#include "GatherCommand.h"
#include "../WorkerUnit.h"
#include "MovementCommand.h"

UGatherCommand::UGatherCommand()
{
	this->ResourceRef = nullptr;

	this->OnReachResourceDelegate.BindUFunction(this, FName("OnReachResource"));
}

void UGatherCommand::Execute()
{
	// TODO uncomment this.
	if (/*this->ResourceRef == nullptr || */this->UnitRef == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	// TODO don't do it like this always use the resource from the commmand.
	AActor* targetResource = this->ResourceRef != nullptr ? this->ResourceRef : asWorker->GetTargetResource();
	FGatherRequest gatherRequest = FGatherRequest(targetResource, this->OnSuccess, this->OnFail);
	asWorker->SetGatherRequest(gatherRequest);
	if (asWorker->GetTargetResource() == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(asWorker->GetTargetResource()->GetActorLocation());
	movementCommmand->SetOnCommandSuccess(this->OnReachResourceDelegate);
	movementCommmand->SetOnCommandFail(this->OnFail);
	asWorker->ExecuteCommand(movementCommmand);
}

void UGatherCommand::SetResource(AActor* Resource)
{
	this->ResourceRef = Resource;
}

void UGatherCommand::OnReachResource()
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	asWorker->ExtractResource();
}
