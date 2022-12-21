// Copyright: For learning purposes, Mono Zubiria.


#include "WorkerUnit.h"
#include "AIController.h"
#include "AITypes.h"
//#include "Kismet/GameplayStatics.h"
#include "UnitGathererComponent.h"
#include "UnitAttackComponent.h"

// Sets default values
AWorkerUnit::AWorkerUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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

void AWorkerUnit::ExecuteCommand(UUnitCommand* Command)
{
	this->bIsRunningCommand = true;

	Command->Execute();
}

bool AWorkerUnit::GetIsRunningCommand()
{
	return this->bIsRunningCommand;
}

UUnitComponent* AWorkerUnit::GetUnitComponent() const
{
	return this->UnitComponent;
}

UCommanderComponent* AWorkerUnit::GetOwnerCommander() const
{
	return this->OwnerCommander;
}

void AWorkerUnit::SetOwnerCommander(UCommanderComponent* Commander)
{
	this->OwnerCommander = Commander;
}

void AWorkerUnit::StopAllActions()
{
	UE_LOG(LogTemp, Warning, TEXT("StopAllActions"));

	this->FindComponentByClass<UUnitAttackComponent>()->ClearAttackRequest();
	this->FindComponentByClass<UUnitGathererComponent>()->ClearGatherRequest();

	AAIController* controller = Cast<AAIController>(this->GetController());
	controller->StopMovement();

	this->UnitComponent->SetCurrentState(EUnitStates::Idle);

	this->OnStopAll();

	this->bIsRunningCommand = false;
}

