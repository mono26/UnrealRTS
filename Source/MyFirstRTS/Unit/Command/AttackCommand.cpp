// Copyright: For learning purposes, Mono Zubiria.


#include "AttackCommand.h"
#include "../WorkerUnit.h"
#include "MovementCommand.h"
#include "../../Component/InteractableComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Component/UnitAttackComponent.h"

UAttackCommand::UAttackCommand() : Super()
{
	this->AttackTargetRef = nullptr;

	this->OnReachAttackTargetDelegate.BindUFunction(this, FName("OnReachAttackTarget"));
}

void UAttackCommand::Execute()
{
	if (this->AttackTargetRef == nullptr || this->UnitRef == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid data for attack."));
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

	UUnitAttackComponent* attackComponent = asWorker->FindComponentByClass<UUnitAttackComponent>();

	FAttackRequest request = FAttackRequest(this->AttackTargetRef, this->OnSuccess, this->OnFail);
	attackComponent->SetAttackRequest(request);

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
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);

	UUnitAttackComponent* attackComponent = asWorker->FindComponentByClass<UUnitAttackComponent>();

	if (attackComponent->GetAttackTarget() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No attack target."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	FVector currentLocation = asWorker->GetActorLocation();
	FVector targetLocation = attackComponent->GetAttackTarget()->GetActorLocation();
	targetLocation.Z = currentLocation.Z;

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(currentLocation, targetLocation);
	asWorker->SetActorRotation(lookAtRotation);

	attackComponent->ExecuteAttack();
}