// Copyright: For learning purposes, Mono Zubiria.


#include "GatherCommand.h"
#include "../WorkerUnit.h"
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

	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);

	UUnitGathererComponent* gatherComponent = asWorker->FindComponentByClass<UUnitGathererComponent>();

	FGatherRequest gatherRequest = FGatherRequest(this->ResourceRef, this->OnSuccess, this->OnFail);
	gatherComponent->SetGatherRequest(gatherRequest);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteGatherCommand"));

	UMovementCommand* movementCommmand = NewObject<UMovementCommand>();
	movementCommmand->SetUnit(this->UnitRef);
	movementCommmand->SetTargetPosition(gatherComponent->GetTargetResource()->GetActorLocation());
	movementCommmand->SetOnSuccess(this->OnReachResourceDelegate);
	movementCommmand->SetOnFail(this->OnFail);
	asWorker->ExecuteCommand(movementCommmand);
}

void UGatherCommand::SetResource(AActor* Resource)
{
	this->ResourceRef = Resource;
}

void UGatherCommand::OnReachResource()
{
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(this->UnitRef);

	UUnitGathererComponent* gatherComponent = asWorker->FindComponentByClass<UUnitGathererComponent>();

	if (gatherComponent->GetTargetResource() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No target resource."));
		this->OnFail.ExecuteIfBound();
		return;
	}

	FVector currentLocation = asWorker->GetActorLocation();
	FVector resourceLocation = gatherComponent->GetTargetResource()->GetActorLocation();
	resourceLocation.Z = currentLocation.Z;

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(currentLocation, resourceLocation);
	asWorker->SetActorRotation(lookAtRotation);

	gatherComponent->ExtractResource();
}
