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
	asWorker->SetTargetResource(this->ResourceRef != nullptr ? this->ResourceRef : asWorker->GetResource());
	if (asWorker->GetResource() == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExecuteGatherCommand"));

	// TODO move to resource
	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(asWorker->GetResource()->GetActorLocation());
	movementCommmand->SetOnCommandSuccess(this->OnReachResourceDelegate);
	movementCommmand->SetOnCommandFail(this->OnReachResourceFailDelegate);
	asWorker->ExecuteCommand(movementCommmand);
}

void UGatherCommand::SetResource(AActor* Resource)
{
	this->ResourceRef = Resource;
}

void UGatherCommand::OnReachResource()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReachResource"));

	// TODO extract resource
}

void UGatherCommand::OnReachResourceFail()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReachResourceFail"));

	this->OnFail.ExecuteIfBound();
}
