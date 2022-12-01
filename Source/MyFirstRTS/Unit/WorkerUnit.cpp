// Copyright: For learning purposes, Mono Zubiria.


#include "WorkerUnit.h"
#include "AIController.h"
#include "AITypes.h"
#include "Kismet/GameplayStatics.h"
#include "UnitGathererComponent.h"

// Sets default values
AWorkerUnit::AWorkerUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->AttackRequest = new FAttackRequest();
	this->AttackTimer = nullptr;

	this->OnExecuteAttackDelegate.BindUFunction(this, FName("OnExecuteAttack"));
}

// Called when the game starts or when spawned
void AWorkerUnit::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, this->GetActorNameOrLabel());

	this->UnitComponent = this->FindComponentByClass<UUnitComponent>();
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

void AWorkerUnit::ExecuteAttack()
{
	if (this->GetAttackTarget() == nullptr) {
		return;
	}

	this->AttackRequest->SetDistanceToTarget(FVector::DistSquared(this->GetActorLocation(), this->GetAttackTarget()->GetActorLocation()));

	this->AttackTimer = new FExtendedTimer(&this->GetWorld()->GetTimerManager(), this->UnitComponent->AttackSwingDuration, this->OnExecuteAttackDelegate, this->AttackRequest->GetOnFail());

	this->UnitComponent->SetCurrentState(EUnitStates::Attacking);
}

void AWorkerUnit::ClearAttackRequest()
{
	UE_LOG(LogTemp, Warning, TEXT("Clear attack request."));

	this->SetAttackRequest(FAttackRequest());

	if (this->AttackTimer != nullptr) {
		FExtendedTimer* timer = this->AttackTimer;
		this->AttackTimer = nullptr;
		timer->Stop();
	}
}

AActor* AWorkerUnit::GetAttackTarget() const
{
	return this->AttackRequest->GetAttackTargetRef();
}

void AWorkerUnit::OnExecuteAttack()
{
	AActor* target = this->GetAttackTarget();
	if (target == nullptr) {
		this->AttackRequest->GetOnFail().ExecuteIfBound();
		return;
	}

	float currentDistance = FVector::DistSquared(this->GetActorLocation(), this->GetAttackTarget()->GetActorLocation());
	if (this->AttackRequest->GetDistanceToTarget() > currentDistance) {
		this->OwnerCommander->ExecuteAttackCommand(this->GetAttackTarget(), this, this->AttackRequest->GetOnSuccess(), this->AttackRequest->GetOnFail());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Deal damage to %s."), *target->GetName());

	UGameplayStatics::ApplyDamage(target, this->UnitComponent->AttackDamage, this->GetController(), this, nullptr);

	this->AttackRequest->GetOnSuccess().ExecuteIfBound();
}

void AWorkerUnit::SetAttackRequest(FAttackRequest Request)
{
	UE_LOG(LogTemp, Warning, TEXT("SetAttackRequest"));

	AActor* oldTarget = this->GetAttackTarget();

	this->AttackRequest->SetAttackTargetRef(Request.GetAttackTargetRef());
	this->AttackRequest->SetOnSuccess(Request.GetOnSuccess());
	this->AttackRequest->SetOnFail(Request.GetOnFail());

	if (this->OnTargetChangedEvent.IsBound()) {
		this->OnTargetChangedEvent.Broadcast(oldTarget, this->GetAttackTarget());
	}
}

void AWorkerUnit::ExecuteCommand(UUnitCommand* Command)
{
	this->bIsRunningCommand = true;

	Command->Execute();
}

bool AWorkerUnit::GetIsRunningCommand()
{
	return this->bIsRunningCommand;
}

void AWorkerUnit::SetOwnerCommander(UCommanderComponent* Commander)
{
	this->OwnerCommander = Commander;
}

void AWorkerUnit::StopAllActions()
{
	AAIController* controller = Cast<AAIController>(this->GetController());
	controller->StopMovement();

	this->ClearAttackRequest();
	this->GetOwner()->FindComponentByClass<UUnitGathererComponent>()->ClearGatherRequest();

	this->UnitComponent->SetCurrentState(EUnitStates::Idle);

	this->OnStopAll();

	this->bIsRunningCommand = false;
}

