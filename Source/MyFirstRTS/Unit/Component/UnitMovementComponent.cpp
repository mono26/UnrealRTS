// Copyright: For learning purposes, Mono Zubiria.


#include "UnitMovementComponent.h"
#include "AIController.h"
#include "AITypes.h"
#include "UnitComponent.h"

// Sets default values for this component's properties
UUnitMovementComponent::UUnitMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UUnitMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AAIController* controller = Cast<AAIController>(Cast<APawn>(this->GetOwner())->GetController());

	UPathFollowingComponent* pathComponent = controller->GetPathFollowingComponent();
	pathComponent->OnRequestFinished.AddUObject(this, &UUnitMovementComponent::OnMoveRequestCompleted);
}

// Called every frame
void UUnitMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUnitMovementComponent::MoveToPosition(FVector Position, FActionSignature OnSuccess, FActionSignature OnFail)
{
	AAIController* controller = Cast<AAIController>(Cast<APawn>(this->GetOwner())->GetController());
	if (controller == nullptr) {
		return;
	}

	UPathFollowingComponent* pathComponent = controller->GetPathFollowingComponent();

	EPathFollowingRequestResult::Type requestResult = controller->MoveToLocation(
		Position + FVector(0, 0, 0.1f),
		60.0f /*TODO use interactable size.*/,
		false
	);

	if (requestResult == EPathFollowingRequestResult::Failed) {
		OnFail.ExecuteIfBound();
	}
	else if (requestResult == EPathFollowingRequestResult::AlreadyAtGoal) {
		OnSuccess.ExecuteIfBound();
	}
	else {
		FAIRequestID requestID = pathComponent->GetCurrentRequestId();
		FMovementRequest request = FMovementRequest(requestID.GetID(), OnSuccess, OnFail);
		MovementRequest.Add(requestID.GetID(), request);

		// TODO maybe let the unit listen to the on start movement event.
		this->GetOwner()->FindComponentByClass<UUnitComponent>()->SetCurrentState(EUnitStates::Moving);

		this->OnStartMovement();
	}
}

void UUnitMovementComponent::MoveToActor(AActor* ActorRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	this->MoveToPosition(ActorRef->GetActorLocation(), OnSuccess, OnFail);
}

void UUnitMovementComponent::OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	uint32 id = RequestID.GetID();
	if (!MovementRequest.Contains(id)) {
		return;
	}

	FMovementRequest* request = MovementRequest.Find(id);
	if (request->GetResquestId() == id) {
		if (Result.IsSuccess()) {
			request->GetOnSuccess().ExecuteIfBound();
		}
		else {
			// Don't trigger callback if the path is aborted by a new path request.
			if (!Result.IsInterrupted()) {
				request->GetOnFail().ExecuteIfBound();
			}
		}
	}

	MovementRequest.Remove(id);
	// TODO: need to check if structs need to be deleted, if so find a way of doing it without crashing the editor.
	// delete request;
}

void UUnitMovementComponent::StopAction()
{
	AAIController* controller = Cast<AAIController>(Cast<APawn>(this->GetOwner())->GetController());
	controller->StopMovement();
}