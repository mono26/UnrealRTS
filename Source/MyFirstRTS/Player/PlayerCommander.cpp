// Copyright: For learning purposes, Mono Zubiria.


#include "PlayerCommander.h"
#include "../Unit/Command/MovementCommand.h"
#include "../Unit/Command/StopCommand.h"

void APlayerCommander::ExecuteAttackCommand(AActor* Target, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail)
{
	if (UnitRef == nullptr) {
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExecuteAttackCommand"));
}

void APlayerCommander::ExecuteMovementCommand(FVector TargetPosition, AActor* UnitRef, FOnCommandUpdateSignature OnSuccess, FOnCommandUpdateSignature OnFail)
{
	if (UnitRef == nullptr) {
		return;
	}

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
	if (UnitRef == nullptr) {
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(UnitRef);
	if (asWorker == nullptr) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExecuteStopCommand"));

	UStopCommand* stopCommand = NewObject<UStopCommand>();
	stopCommand->SetUnitRef(UnitRef);
	asWorker->ExecuteCommand(stopCommand);
}
