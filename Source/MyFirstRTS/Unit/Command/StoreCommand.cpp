// Copyright: For learning purposes, Mono Zubiria.


#include "StoreCommand.h"
#include "../WorkerUnit.h"

UStoreCommand::UStoreCommand()
{
	this->StorageRef = nullptr;
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
}

void UStoreCommand::SetStorage(AActor* Storage)
{
	this->StorageRef = Storage;
}
