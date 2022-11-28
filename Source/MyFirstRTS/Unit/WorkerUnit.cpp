// Copyright: For learning purposes, Mono Zubiria.


#include "WorkerUnit.h"
#include "AIController.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/PlayerCommander.h"

// Sets default values
AWorkerUnit::AWorkerUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->AttackTargetRef = nullptr;

	this->OnExtractResourceDelegate.BindUFunction(this, FName("OnExtractResource"));

	this->GatherTimer = nullptr;

	this->CarriedResource = FResource();
}

// Called when the game starts or when spawned
void AWorkerUnit::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, this->GetActorNameOrLabel());

	this->UnitComponent = this->FindComponentByClass<UUnitComponent>();

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
	UE_LOG(LogTemp, Warning, TEXT("SetAttackTarget"));

	AActor* oldTarget = this->AttackTargetRef;
	this->AttackTargetRef = AttackTarget;

	if (this->OnTargetChangedEvent.IsBound()) {
		this->OnTargetChangedEvent.Broadcast(oldTarget, this->AttackTargetRef);
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
		return;
	}

	FMovementRequest* request = MovementRequest.Find(id);
	if (request->GetResquestId() == id) {
		if (Result.IsSuccess()) {
			request->GetOnSuccess().ExecuteIfBound();
		}
		else {
			request->GetOnFail().ExecuteIfBound();
		}
	}

	MovementRequest.Remove(id);
	// TODO: need to check if structs need to be deleted, if so find a way of doing it without crashing the editor.
	// delete request;
}

AActor* AWorkerUnit::GetTargetResource()
{
	return this->GatherRequest.GetResourceRef();
}

void AWorkerUnit::SetGatherRequest(FGatherRequest Request)
{
	this->GatherRequest = Request;
}

void AWorkerUnit::ExtractResource()
{
	if (this->GatherRequest.GetResourceRef() == nullptr) {
		this->GatherRequest.GetOnFail().ExecuteIfBound();
		return;
	}

	UResourceComponent* resourceComponent = this->GatherRequest.GetResourceRef()->FindComponentByClass<UResourceComponent>();
	if (resourceComponent == nullptr) {
		this->GatherRequest.GetOnFail().ExecuteIfBound();
		return;
	}

	if (this->CarriedResource.ResourceType == resourceComponent->ResourceType) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Already have this resource."));

		this->GatherRequest.GetOnSuccess().ExecuteIfBound();
		return;
	}

	if (!resourceComponent->CanGather()) {
		this->GatherRequest.GetOnFail().ExecuteIfBound();
		return;
	}

	this->GatherTimer = new FExtendedTimer(&GetWorld()->GetTimerManager(), 3.0f, this->OnExtractResourceDelegate, this->GatherRequest.GetOnFail());

	this->UnitComponent->SetCurrentState(EUnitStates::Gathering);
}

void AWorkerUnit::OnExtractResource()
{
	UResourceComponent* resourceComponent = this->GatherRequest.GetResourceRef()->FindComponentByClass<UResourceComponent>();
	if (resourceComponent == nullptr) {
		this->GatherRequest.GetOnFail().ExecuteIfBound();
		return;
	}

	this->CarriedResource = resourceComponent->GetGatheredResource();

	this->GatherRequest.GetOnSuccess().ExecuteIfBound();
}

void AWorkerUnit::StoreResource()
{
	if (this->CarriedResource.ResourceType == EResourceType::None || this->CarriedResource.ResourceAmount <= 0) {
		return;
	}

	APlayerCommander* commander = Cast<APlayerCommander>(UGameplayStatics::GetPlayerController(this, 0));
	commander->ReceiveResources(this->CarriedResource.ResourceType, this->CarriedResource.ResourceAmount);
	// TODO delete old resource? Or maybe just create a pointer and set the inner values.
	this->CarriedResource = FResource();
}

void AWorkerUnit::ExecuteCommand(UUnitCommand* Command)
{
	this->bIsRunningCommand = true;

	if (this->GatherTimer != nullptr) {
		FExtendedTimer* timer = this->GatherTimer;
		this->GatherTimer = nullptr;
		timer->Stop();
	}

	this->SetAttackTarget(nullptr);

	Command->Execute();
}

bool AWorkerUnit::GetIsRunningCommand()
{
	return this->bIsRunningCommand;
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
		FExtendedTimer* timer = this->GatherTimer;
		this->GatherTimer = nullptr;
		timer->Stop();
	}

	this->SetAttackTarget(nullptr);
	this->UnitComponent->SetCurrentState(EUnitStates::Idle);

	this->OnStopAll();

	this->bIsRunningCommand = false;
}

