// Copyright: For learning purposes, Mono Zubiria.


#include "AttackCommand.h"
#include "../WorkerUnit.h"
#include "MovementCommand.h"
#include "../../Component/InteractableComponent.h"

UAttackCommand::UAttackCommand() : Super()
{
	this->AttackTargetRef = nullptr;

	this->OnReachAttackTargetDelegate.BindUFunction(this, FName("OnReachAttackTarget"));
	this->OnReachAttackTargetFailDelegate.BindUFunction(this, FName("OnReachAttackTargetFail"));
}

void UAttackCommand::SetAttackTarget(AActor* AttackTarget)
{
	this->AttackTargetRef = AttackTarget;
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
	UE_LOG(LogTemp, Warning, TEXT("TryExecuteAttackCommand"));

	// TODO uncomment this.
	if (/*this->AttackTargetRef == nullptr || */this->UnitRef == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Not a worker."));

		this->OnFail.ExecuteIfBound();
		return;
	}

	// TODO don't do it like this always use the resource from the commmand.
	AActor* attackTarget = this->AttackTargetRef != nullptr ? this->AttackTargetRef : asWorker->GetAttackTarget();
	FAttackRequest request = FAttackRequest(attackTarget, this->OnSuccess, this->OnFail);
	asWorker->SetAttackRequest(request);
	if (asWorker->GetAttackTarget() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No attack target."));

		this->OnFail.ExecuteIfBound();
		return;
	}

	UInteractableComponent* interactableComponent = asWorker->GetAttackTarget()->FindComponentByClass<UInteractableComponent>();
	if (interactableComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No interactable target."));

		this->OnFail.ExecuteIfBound();
		return;
	}

	FVector interactPosition = interactableComponent->GetClosestInteractionPositionTo(this->UnitRef);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteAttackCommand"));

	// TODO move to target
	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(interactPosition);
	movementCommmand->SetOnSuccess(this->OnReachAttackTargetDelegate);
	movementCommmand->SetOnFail(this->OnReachAttackTargetFailDelegate);
	asWorker->ExecuteCommand(movementCommmand);
	// TODO attack after reaching target.
}