// Copyright: For learning purposes, Mono Zubiria.

#include "MovementCommand.h"
#include "../Component/UnitMovementComponent.h"

UMovementCommand::UMovementCommand() : Super()
{
	this->TargetPosition = FVector::Zero();

	this->OnReachedPositionDelegate.BindUFunction(this, FName("OnReachTargetPosition"));
	this->OnReachPositionFailDelegate.BindUFunction(this, FName("OnReachTargetPositionFail"));
}

void UMovementCommand::SetAcceptanceRange(float Range)
{
	this->AcceptanceRange = Range;
}

void UMovementCommand::SetTargetPosition(FVector Position)
{
	this->TargetPosition = Position;
}

void UMovementCommand::Execute()
{
	if (this->UnitRef == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid data."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	UUnitMovementComponent* movementComponent = this->UnitRef->FindComponentByClass<UUnitMovementComponent>();
	if (movementComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No movement components."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("ExecuteMovementCommand"));

	movementComponent->MoveToPosition(this->TargetPosition, this->AcceptanceRange, this->OnReachedPositionDelegate, this->OnReachPositionFailDelegate);
}

void UMovementCommand::OnReachTargetPosition()
{
	this->OnSuccess.ExecuteIfBound();
}

void UMovementCommand::OnReachTargetPositionFail()
{
	this->OnFail.ExecuteIfBound();
}
