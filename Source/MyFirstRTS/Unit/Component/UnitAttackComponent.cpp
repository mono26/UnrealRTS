// Copyright: For learning purposes, Mono Zubiria.


#include "UnitAttackComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../RTSUnit.h"
#include "../../Component/InteractableComponent.h"

// Sets default values for this component's properties
UUnitAttackComponent::UUnitAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	this->AttackRequest = new FAttackRequest();
	this->AttackTimer = nullptr;

	this->OnExecuteAttackDelegate.BindUFunction(this, FName("OnExecuteAttack"));
}

// Called when the game starts
void UUnitAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UUnitAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUnitAttackComponent::ExecuteAttack()
{
	if (this->GetAttackTarget() == nullptr) {
		return;
	}

	ARTSUnit* asWorker = Cast<ARTSUnit>(this->GetOwner());

	UInteractableComponent* interactableComponent = this->GetAttackTarget()->FindComponentByClass<UInteractableComponent>();

	this->AttackRequest->SetDistanceToTarget(FVector::DistSquared(this->GetOwner()->GetActorLocation(), interactableComponent->GetClosestInteractionPositionTo(this->GetOwner())));

	float swingDuration = asWorker->GetUnitComponent()->AttackSwingDuration;

	this->AttackTimer = new FExtendedTimer(&this->GetWorld()->GetTimerManager(), swingDuration, this->OnExecuteAttackDelegate, this->AttackRequest->GetOnFail());

	asWorker->GetUnitComponent()->SetCurrentState(EUnitStates::Attacking);
}

void UUnitAttackComponent::ClearAttackRequest()
{
	UE_LOG(LogTemp, Warning, TEXT("Clear attack request."));

	this->SetAttackRequest(FAttackRequest());

	if (this->AttackTimer != nullptr) {
		FExtendedTimer timer = *this->AttackTimer;

		this->AttackTimer = nullptr;

		timer.Stop();
	}
}

AActor* UUnitAttackComponent::GetAttackTarget() const
{
	return this->AttackRequest->GetAttackTargetRef();
}

void UUnitAttackComponent::OnExecuteAttack()
{
	AActor* target = this->GetAttackTarget();
	if (target == nullptr) {
		this->AttackRequest->GetOnFail().ExecuteIfBound();
		return;
	}

	ARTSUnit* asWorker = Cast<ARTSUnit>(this->GetOwner());

	UInteractableComponent* interactableComponent = this->GetAttackTarget()->FindComponentByClass<UInteractableComponent>();

	float currentDistance = FVector::DistSquared(this->GetOwner()->GetActorLocation(), interactableComponent->GetClosestInteractionPositionTo(this->GetOwner()));
	float attackRange = asWorker->GetUnitComponent()->AttackRange;
	if (this->AttackRequest->GetDistanceToTarget() < /*currentDistance*/attackRange * attackRange) {
		UE_LOG(LogTemp, Warning, TEXT("Not in range to deal damage."), *target->GetName());

		asWorker->GetOwnerCommander()->CommandComponent->ExecuteAttackCommand(this->GetAttackTarget(), asWorker, this->AttackRequest->GetOnSuccess(), this->AttackRequest->GetOnFail());

		return;
	}

	UGameplayStatics::ApplyDamage(target, asWorker->GetUnitComponent()->AttackDamage, asWorker->GetController(), asWorker, nullptr);

	this->AttackRequest->GetOnSuccess().ExecuteIfBound();
}

void UUnitAttackComponent::StopAction()
{
	this->ClearAttackRequest();
}

void UUnitAttackComponent::SetAttackRequest(FAttackRequest Request)
{
	UE_LOG(LogTemp, Warning, TEXT("SetAttackRequest"));

	AActor* oldTarget = this->GetAttackTarget();

	this->AttackRequest->SetAttackTargetRef(Request.GetAttackTargetRef());
	this->AttackRequest->SetOnSuccess(Request.GetOnSuccess());
	this->AttackRequest->SetOnFail(Request.GetOnFail());

	if (this->OnTargetChangedEvent.IsBound()) {
		this->OnTargetChangedEvent.Broadcast(oldTarget, Request.GetAttackTargetRef());
	}
}