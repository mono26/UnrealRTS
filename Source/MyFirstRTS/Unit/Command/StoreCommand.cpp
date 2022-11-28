// Copyright: For learning purposes, Mono Zubiria.


#include "StoreCommand.h"
#include "../WorkerUnit.h"
#include "MovementCommand.h"
#include "../../Component/InteractableComponent.h"
#include "DrawDebugHelpers.h"

UStoreCommand::UStoreCommand()
{
	this->StorageRef = nullptr;

	this->OnReachStorageDelegate.BindUFunction(this, FName("OnReachStorage"));
}

void UStoreCommand::Execute()
{
	if (this->StorageRef == nullptr || this->UnitRef == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	UInteractableComponent* interactableComponent = this->StorageRef->FindComponentByClass<UInteractableComponent>();
	if (interactableComponent == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	USceneComponent* point = interactableComponent->GetClosestInteractionPointTo(this->UnitRef);
	if (point == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	// UE_LOG(LogTemp, Warning, TEXT("ExecuteStoreCommand"));

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(point->GetComponentLocation());
	movementCommmand->SetOnSuccess(this->OnReachStorageDelegate);
	movementCommmand->SetOnFail(this->OnFail);
	asWorker->ExecuteCommand(movementCommmand);
}

void UStoreCommand::SetStorage(AActor* Storage)
{
	this->StorageRef = Storage;
}

void UStoreCommand::OnReachStorage()
{
	// TODO extract resource
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Not a worker."));

		this->OnFail.ExecuteIfBound();
		return;
	}

	asWorker->StoreResource();

	this->OnSuccess.Execute();
}
