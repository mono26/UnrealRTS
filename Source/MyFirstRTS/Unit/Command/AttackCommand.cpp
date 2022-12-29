// Copyright: For learning purposes, Mono Zubiria.


#include "AttackCommand.h"
#include "../RTSUnit.h"
#include "MovementCommand.h"
#include "../../Component/InteractableComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Component/UnitAttackComponent.h"
#include "../../Component/HealthComponent.h"

UAttackCommand::UAttackCommand() : Super()
{
	this->AttackTarget = nullptr;

	this->OnReachAttackTargetDelegate.BindUFunction(this, FName("OnReachAttackTarget"));
}

void UAttackCommand::Execute()
{
	if (this->AttackTarget == nullptr || this->UnitRef == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid data for attack."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	UHealthComponent* healthComponent = this->UnitRef->FindComponentByClass<UHealthComponent>();
	if (healthComponent->GetHealthCurrent() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid target for attack."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	UInteractableComponent* interactableComponent = this->AttackTarget->FindComponentByClass<UInteractableComponent>();

	ARTSUnit* asWorker = Cast<ARTSUnit>(this->UnitRef);

	UUnitAttackComponent* attackComponent = asWorker->FindComponentByClass<UUnitAttackComponent>();

	FAttackRequest request = FAttackRequest(this->AttackTarget, this->OnSuccess, this->OnFail);
	attackComponent->SetAttackRequest(request);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteAttackCommand"));

	FVector interactPosition = interactableComponent->GetClosestInteractionPositionTo(this->UnitRef);

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(interactPosition);
	movementCommmand->SetAcceptanceRange(asWorker->GetUnitComponent()->AttackRange - 1.0f);
	movementCommmand->SetOnSuccess(this->OnReachAttackTargetDelegate);
	movementCommmand->SetOnFail(this->OnFail);
	asWorker->ExecuteCommand(movementCommmand);
}

void UAttackCommand::SetAttackTarget(AActor* Target)
{
	this->AttackTarget = Target;
}

void UAttackCommand::OnReachAttackTarget()
{
	ARTSUnit* asWorker = Cast<ARTSUnit>(this->UnitRef);

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