// Copyright: For learning purposes, Mono Zubiria.


#include "WorkerUnit.h"
#include "AIController.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "../Resource/ResourceComponent.h"

// Sets default values
AWorkerUnit::AWorkerUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->AttackTargetRef = nullptr;
}

// Called when the game starts or when spawned
void AWorkerUnit::BeginPlay()
{
	Super::BeginPlay();
	
	if (this->GetController() == nullptr) {
		return;
	}

	AAIController* controller = Cast<AAIController>(this->GetController());
	if (controller == nullptr) {
		return;
	}

	UPathFollowingComponent* pathComponent = controller->GetPathFollowingComponent();
	pathComponent->OnRequestFinished.AddUObject(this, &AWorkerUnit::OnMoveRequestCompleted);
}

// Called every frame
void AWorkerUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorkerUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor* AWorkerUnit::GetAttackTarget()
{
	return this->AttackTargetRef;
}

void AWorkerUnit::MoveToPosition(FVector Position, FOnMovementUpdateSignature OnSuccess, FOnMovementUpdateSignature OnFail)
{
	if (this->GetController() == nullptr) {
		return;
	}

	AAIController* controller = Cast<AAIController>(this->GetController());
	if (controller == nullptr) {
		return;
	}

	UPathFollowingComponent* pathComponent = controller->GetPathFollowingComponent();

	EPathFollowingRequestResult::Type requestResult = controller->MoveToLocation(
		Position, 
		50.0f /*TODO use interactable size.*/,
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
	}
}

void AWorkerUnit::MoveToActor(AActor* ActorRef, FOnMovementUpdateSignature OnSuccess, FOnMovementUpdateSignature OnFail)
{
	this->MoveToPosition(ActorRef->GetActorLocation(), OnSuccess, OnFail);
}

void AWorkerUnit::OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	uint32 id = RequestID.GetID();
	if (!MovementRequest.Contains(id)) {
		return;
	}

	FMovementRequest* request = MovementRequest.Find(id);
	if (request->requestId == id) {
		if (Result.IsSuccess()) {
			request->OnSuccess.ExecuteIfBound();
		}
		else {
			request->OnFail.ExecuteIfBound();
		}
	}

	MovementRequest.Remove(id);
	// TODO: need to check if structs need to be deleted, if so find a way of doing it without crashing the editor.
	// delete request;
}

void AWorkerUnit::ExtractResource(AActor* ResourceRef)
{
	if (ResourceRef == nullptr) {
		return;
	}

	UResourceComponent* resourceComponent = Cast<UResourceComponent>(ResourceRef->GetComponentByClass(UResourceComponent::StaticClass()));
	if (resourceComponent == nullptr) {
		return;
	}
}

void AWorkerUnit::OnResourceReached(AActor* ResourceRef)
{
	if (ResourceRef == nullptr) {
		return;
	}

	UResourceComponent* resourceComponent = Cast<UResourceComponent>(ResourceRef->GetComponentByClass(UResourceComponent::StaticClass()));
	if (resourceComponent == nullptr) {
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(this->GatherTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(this->GatherTimerHandle, [&]()
		{
			// Extract the resource.
			this->ExtractResource(ResourceRef);
		}, 3, false);
}

void AWorkerUnit::SetAttackTarget(AActor* TargetRef)
{
	AActor* oldTarget = this->AttackTargetRef;
	this->AttackTargetRef = TargetRef;

	if (this->OnTargetChanged.IsBound()) {
		this->OnTargetChanged.Broadcast(oldTarget, this->AttackTargetRef);
	}
}

