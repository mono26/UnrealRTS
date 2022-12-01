// Copyright: For learning purposes, Mono Zubiria.


#include "AttackCommand.h"
#include "../WorkerUnit.h"
#include "MovementCommand.h"
#include "../../Component/InteractableComponent.h"
#include "Kismet/KismetMathLibrary.h"

UAttackCommand::UAttackCommand() : Super()
{
	this->AttackTargetRef = nullptr;

	this->OnReachAttackTargetDelegate.BindUFunction(this, FName("OnReachAttackTarget"));
}

void UAttackCommand::Execute()
{
	if (this->AttackTargetRef == nullptr || this->UnitRef == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	UInteractableComponent* interactableComponent = this->AttackTargetRef->FindComponentByClass<UInteractableComponent>();
	if (interactableComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No interactable target."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Not a worker."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	FAttackRequest request = FAttackRequest(this->AttackTargetRef, this->OnSuccess, this->OnFail);
	asWorker->SetAttackRequest(request);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteAttackCommand"));

	FVector interactPosition = interactableComponent->GetClosestInteractionPositionTo(this->UnitRef);

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(interactPosition);
	movementCommmand->SetOnSuccess(this->OnReachAttackTargetDelegate);
	movementCommmand->SetOnFail(this->OnFail);
	asWorker->ExecuteCommand(movementCommmand);
}

void UAttackCommand::SetAttackTarget(AActor* AttackTarget)
{
	this->AttackTargetRef = AttackTarget;
}

void UAttackCommand::OnReachAttackTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReachAttackTarget"));

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);
	if (asWorker == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Not a worker."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	if (asWorker->GetAttackTarget() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No attack target."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(asWorker->GetActorLocation(), asWorker->GetAttackTarget()->GetActorLocation());
	asWorker->SetActorRotation(lookAtRotation);

	asWorker->ExecuteAttack();
}