// Copyright: For learning purposes, Mono Zubiria.


#include "PlayerCommander.h"
#include "../Unit/Command/MovementCommand.h"
#include "../Unit/Command/StopCommand.h"
#include "../Game/MyFirstRTSGameMode.h"
#include "../Unit/Command/GatherCommand.h"
#include "../Unit/Command/StoreCommand.h"

void APlayerCommander::ExecuteAttackCommand(AActor* Target, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}
}

void APlayerCommander::ExecuteGatherCommand(AActor* Resource, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UGatherCommand* gatherCommand = NewObject<UGatherCommand>();
	gatherCommand->SetUnit(UnitRef);
	gatherCommand->SetResource(Resource);
	gatherCommand->SetOnCommandSuccess(OnSuccess);
	gatherCommand->SetOnCommandFail(OnFail);
	asWorker->ExecuteCommand(gatherCommand);
}

void APlayerCommander::ExecuteMovementCommand(FVector TargetPosition, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(UnitRef);
	movementCommmand->SetTargetPosition(TargetPosition);
	movementCommmand->SetOnCommandSuccess(OnSuccess);
	movementCommmand->SetOnCommandFail(OnFail);
	asWorker->ExecuteCommand(movementCommmand);
}

void APlayerCommander::ExecuteStopCommand(AActor* UnitRef)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UStopCommand* stopCommand = NewObject<UStopCommand>();
	stopCommand->SetUnit(UnitRef);
	asWorker->ExecuteCommand(stopCommand);
}

void APlayerCommander::ExecuteStoreCommand(AActor* Storage, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UStoreCommand* storeCommand = NewObject<UStoreCommand>();
	storeCommand->SetUnit(UnitRef);
	storeCommand->SetStorage(Storage);
	storeCommand->SetOnCommandSuccess(OnSuccess);
	storeCommand->SetOnCommandFail(OnFail);
	asWorker->ExecuteCommand(storeCommand);
}

AActor* APlayerCommander::GetPlayerTownhall()
{
	UWorld* world = this->GetWorld();
	AGameModeBase* gameMode = world->GetAuthGameMode();
	AMyFirstRTSGameMode* rtsMode = Cast<AMyFirstRTSGameMode>(gameMode);
	if (rtsMode == nullptr) {
		return nullptr;
	}

	return rtsMode->GetPlayerTownhall();
}

void APlayerCommander::ReceiveResources(EResourceType ResourceType, int ResourceAmount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ReceiveResources"));

	if (this->StoredResources.Contains(ResourceType)) {
		this->StoredResources[ResourceType] += ResourceAmount;
	}
	else {
		this->StoredResources.Add(ResourceType, ResourceAmount);
	}

	this->OnReceiveResources(ResourceType);
}
