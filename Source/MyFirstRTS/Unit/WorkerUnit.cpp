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

	this->GatherTimer = nullptr;
}

// Called when the game starts or when spawned
void AWorkerUnit::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, this->GetActorNameOrLabel());

	this->UnitComponent = Cast<UUnitComponent>(this->GetComponentByClass(UUnitComponent::StaticClass()));

	AAIController* controller = Cast<AAIController>(this->GetController());

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

void AWorkerUnit::SetAttackTarget(AActor* AttackTarget)
{
	AActor* oldTarget = this->AttackTargetRef;
	this->AttackTargetRef = AttackTarget;

	if (this->OnTargetChanged.IsBound()) {
		this->OnTargetChanged.Broadcast(oldTarget, this->AttackTargetRef);
	}
}

void AWorkerUnit::MoveToPosition(FVector Position, FActionSignature OnSuccess, FActionSignature OnFail)
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

		this->UnitComponent->SetCurrentState(EUnitStates::Moving);

		this->OnStartMovement();
	}
}

void AWorkerUnit::MoveToActor(AActor* ActorRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	this->MoveToPosition(ActorRef->GetActorLocation(), OnSuccess, OnFail);
}

void AWorkerUnit::OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	uint32 id = RequestID.GetID();
	if (!MovementRequest.Contains(id)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No request found."));
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

AActor* AWorkerUnit::GetResource()
{
	return this->TargetResourceRef;
}

void AWorkerUnit::SetTargetResource(AActor* TargetResource)
{
	this->TargetResourceRef = TargetResource;
}

void AWorkerUnit::ExtractResource(AActor* ResourceRef, FActionSignature OnSuccess, FActionSignature OnFail)
{
	if (ResourceRef == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No resource actor."));

		OnFail.ExecuteIfBound();
		return;
	}

	UResourceComponent* resourceComponent = Cast<UResourceComponent>(ResourceRef->GetComponentByClass(UResourceComponent::StaticClass()));
	if (resourceComponent == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No resource component."));

		OnFail.ExecuteIfBound();
		return;
	}

	this->GatherTimer = new FExtendedTimer(&GetWorld()->GetTimerManager(), 3.0f, OnSuccess, OnFail);

	this->UnitComponent->SetCurrentState(EUnitStates::Gathering);
}

void AWorkerUnit::ExecuteCommand(UUnitCommand* Command)
{
	Command->Execute();
}

void AWorkerUnit::StopAllActions()
{
	if (this->GetController() == nullptr) {
		return;
	}

	AAIController* controller = Cast<AAIController>(this->GetController());
	if (controller == nullptr) {
		return;
	}

	controller->StopMovement();

	if (this->GatherTimer != nullptr) {
		this->GatherTimer->Stop();
	}

	this->UnitComponent->SetCurrentState(EUnitStates::Idle);

	this->OnStopAll();
}

