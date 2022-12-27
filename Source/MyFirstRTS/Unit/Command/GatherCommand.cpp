// Copyright: For learning purposes, Mono Zubiria.


#include "GatherCommand.h"
#include "../RTSUnit.h"
#include "MovementCommand.h"
#include "../../Component/InteractableComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Component/UnitGathererComponent.h"

UGatherCommand::UGatherCommand() : Super()
{
	this->ResourceRef = nullptr;

	this->OnReachResourceDelegate.BindUFunction(this, FName("OnReachResource"));
}

void UGatherCommand::Execute()
{
	if (this->ResourceRef == nullptr || this->UnitRef == nullptr) {
		this->OnFail.ExecuteIfBound();
		return;
	}

	UInteractableComponent* interactableComponent = this->ResourceRef->FindComponentByClass<UInteractableComponent>();
	if (interactableComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No interactable target."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	ARTSUnit* asUnit = Cast<ARTSUnit>(this->UnitRef);

	UUnitGathererComponent* gatherComponent = this->UnitRef->FindComponentByClass<UUnitGathererComponent>();

	FGatherRequest gatherRequest = FGatherRequest(this->ResourceRef, this->OnSuccess, this->OnFail);
	gatherComponent->SetGatherRequest(gatherRequest);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteGatherCommand"));

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(gatherComponent->GetTargetResource()->GetActorLocation());
	// TODO get unit size.
	movementCommmand->SetAcceptanceRange(60.0f);
	movementCommmand->SetOnSuccess(this->OnReachResourceDelegate);
	movementCommmand->SetOnFail(this->OnFail);
	asUnit->ExecuteCommand(movementCommmand);
}

void UGatherCommand::SetResource(AActor* Resource)
{
	this->ResourceRef = Resource;
}

void UGatherCommand::OnReachResource()
{
	UUnitGathererComponent* gatherComponent = this->UnitRef->FindComponentByClass<UUnitGathererComponent>();

	if (gatherComponent->GetTargetResource() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No target resource."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	FVector currentLocation = this->UnitRef->GetActorLocation();
	FVector resourceLocation = gatherComponent->GetTargetResource()->GetActorLocation();
	resourceLocation.Z = currentLocation.Z;

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(currentLocation, resourceLocation);
	this->UnitRef->SetActorRotation(lookAtRotation);

	gatherComponent->ExtractResource();
}
