// Copyright: For learning purposes, Mono Zubiria.


#include "AttackCommand.h"
#include "../WorkerUnit.h"
#include "MovementCommand.h"

UAttackCommand::UAttackCommand() : UUnitCommand()
{
	this->AttackTargetRef = nullptr;

	this->OnReachAttackTargetDelegate.BindUFunction(this, FName("OnReachAttackTarget"));
	this->OnReachAttackTargetFailDelegate.BindUFunction(this, FName("OnReachAttackTargetFail"));
}

void UAttackCommand::SetTargetRef(AActor* Target)
{
	this->AttackTargetRef = Target;
}

void UAttackCommand::OnReachAttackTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReachAttackTarget"));
}

void UAttackCommand::OnReachAttackTargetFail()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReachAttackTargetFail"));

	this->OnFail.ExecuteIfBound();
}

void UAttackCommand::Execute()
{
	if (this->AttackTargetRef == nullptr || this->UnitRef == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	asWorker->SetAttackTarget(this->AttackTargetRef);

	// TODO move to target
	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnitRef(this->UnitRef);
	movementCommmand->SetTargetPosition(this->AttackTargetRef->GetActorLocation());
	movementCommmand->SetOnCommandSuccess(this->OnReachAttackTargetDelegate);
	movementCommmand->SetOnCommandFail(this->OnReachAttackTargetFailDelegate);
	asWorker->ExecuteCommand(movementCommmand);
	// TODO attack after reaching target.
}