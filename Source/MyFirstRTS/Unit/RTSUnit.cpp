// Copyright: For learning purposes, Mono Zubiria.


#include "RTSUnit.h"
// #include "Component/UnitComponentInterface.h"

// Sets default values
ARTSUnit::ARTSUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARTSUnit::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, this->GetActorNameOrLabel());

	this->UnitComponent = this->FindComponentByClass<UUnitComponent>();
}

// Called every frame
void ARTSUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARTSUnit::ExecuteCommand(UUnitCommand* Command)
{
	this->bIsRunningCommand = true;

	Command->Execute();
}

bool ARTSUnit::GetIsRunningCommand()
{
	return this->bIsRunningCommand;
}

UUnitComponent* ARTSUnit::GetUnitComponent() const
{
	return this->UnitComponent;
}

UFactionCommander* ARTSUnit::GetOwnerCommander() const
{
	return this->OwnerCommander;
}

void ARTSUnit::SetOwnerCommander(UFactionCommander* Commander)
{
	this->OwnerCommander = Commander;
}

void ARTSUnit::StopAllActions()
{
	//TArray<IUnitComponentInterface*> unitComponents;
	//this->GetComponents<IUnitComponentInterface>(unitComponents, false);
	//for (IUnitComponentInterface* component : unitComponents) {
	//	component->StopAction();
	//}

	this->OnStopAll();

	this->bIsRunningCommand = false;
}