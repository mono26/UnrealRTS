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

void UAttackCommand::SetAttackTarget(AActor* Target)
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
	// TODO uncomment this.
	if (/*this->AttackTargetRef == nullptr || */this->UnitRef == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	// TODO don't do it like this always use the resource from the commmand.
	asWorker->SetAttackTarget(this->AttackTargetRef != nullptr ? this->AttackTargetRef : asWorker->GetAttackTarget());
	if (asWorker->GetAttackTarget() == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("ExecuteAttackCommand"));

	// TODO move to target
	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(this->AttackTargetRef->GetActorLocation());
	movementCommmand->SetOnSuccess(this->OnReachAttackTargetDelegate);
	movementCommmand->SetOnFail(this->OnReachAttackTargetFailDelegate);
	asWorker->ExecuteCommand(movementCommmand);
	// TODO attack after reaching target.
}