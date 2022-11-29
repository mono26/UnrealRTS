// Copyright: For learning purposes, Mono Zubiria.


#include "CommanderComponent.h"
#include "../Unit/Command/MovementCommand.h"
#include "../Unit/Command/StopCommand.h"
#include "../Unit/Command/GatherCommand.h"
#include "../Unit/Command/StoreCommand.h"
#include "../Unit/Command/AttackCommand.h"

// Sets default values for this component's properties
UCommanderComponent::UCommanderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCommanderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCommanderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UCommanderComponent::ExecuteAttackCommand(AActor* AttackTarget, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UAttackCommand* attackCommand = NewObject<UAttackCommand>();
	attackCommand->SetUnit(UnitRef);
	attackCommand->SetAttackTarget(AttackTarget);
	attackCommand->SetOnSuccess(OnSuccess);
	attackCommand->SetOnFail(OnFail);
	asWorker->ExecuteCommand(attackCommand);
}

void UCommanderComponent::ExecuteGatherCommand(AActor* Resource, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UGatherCommand* gatherCommand = NewObject<UGatherCommand>();
	gatherCommand->SetUnit(UnitRef);
	gatherCommand->SetResource(Resource);
	gatherCommand->SetOnSuccess(OnSuccess);
	gatherCommand->SetOnFail(OnFail);
	asWorker->ExecuteCommand(gatherCommand);
}

void UCommanderComponent::ExecuteMovementCommand(FVector TargetPosition, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(UnitRef);
	movementCommmand->SetTargetPosition(TargetPosition);
	movementCommmand->SetOnSuccess(OnSuccess);
	movementCommmand->SetOnFail(OnFail);
	asWorker->ExecuteCommand(movementCommmand);
}

void UCommanderComponent::ExecuteStopCommand(AActor* UnitRef)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UStopCommand* stopCommand = NewObject<UStopCommand>();
	stopCommand->SetUnit(UnitRef);
	asWorker->ExecuteCommand(stopCommand);
}

void UCommanderComponent::ExecuteStoreCommand(AActor* Storage, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	UStoreCommand* storeCommand = NewObject<UStoreCommand>();
	storeCommand->SetUnit(UnitRef);
	storeCommand->SetStorage(Storage);
	storeCommand->SetOnSuccess(OnSuccess);
	storeCommand->SetOnFail(OnFail);
	asWorker->ExecuteCommand(storeCommand);
}