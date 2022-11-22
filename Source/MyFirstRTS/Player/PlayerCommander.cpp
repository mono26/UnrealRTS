// Copyright: For learning purposes, Mono Zubiria.


#include "PlayerCommander.h"
#include "../Unit/Command/MovementCommand.h"
#include "../Unit/Command/StopCommand.h"
#include "../Game/MyFirstRTSGameMode.h"

void APlayerCommander::ExecuteAttackCommand(AActor* Target, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExecuteAttackCommand"));
}

void APlayerCommander::ExecuteGatherCommand(AActor* Resource, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExecuteGatherCommand"));
}

void APlayerCommander::ExecuteMovementCommand(FVector TargetPosition, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExecuteMovementCommand"));

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnitRef(UnitRef);
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

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExecuteStopCommand"));

	UStopCommand* stopCommand = NewObject<UStopCommand>();
	stopCommand->SetUnitRef(UnitRef);
	asWorker->ExecuteCommand(stopCommand);
}

void APlayerCommander::ExecuteStoreCommand(AActor* Storage, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail)
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExecuteStoreCommand"));
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
