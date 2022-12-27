// Copyright: For learning purposes, Mono Zubiria.


#include "StoreCommand.h"
#include "../RTSUnit.h"
#include "MovementCommand.h"
#include "../../Component/InteractableComponent.h"
#include "DrawDebugHelpers.h"
#include "../Component/UnitGathererComponent.h"

UStoreCommand::UStoreCommand() : Super()
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

	UInteractableComponent* interactableComponent = this->StorageRef->FindComponentByClass<UInteractableComponent>();

	ARTSUnit* asWorker = Cast<ARTSUnit>(this->UnitRef);

	FVector interactPosition = interactableComponent->GetClosestInteractionPositionTo(this->UnitRef);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteStoreCommand"));

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(interactPosition);
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
	ARTSUnit* asWorker = Cast<ARTSUnit>(this->UnitRef);

	UUnitGathererComponent* gatherComponent = asWorker->FindComponentByClass<UUnitGathererComponent>();

	gatherComponent->StoreResource();

	this->OnSuccess.Execute();
}
