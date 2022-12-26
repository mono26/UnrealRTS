// Copyright: For learning purposes, Mono Zubiria.


#include "WorkerUnit.h"
#include "AIController.h"
#include "AITypes.h"
#include "Component/UnitGathererComponent.h"
#include "Component/UnitAttackComponent.h"

void AWorkerUnit::StopAllActions()
{
	this->FindComponentByClass<UUnitAttackComponent>()->ClearAttackRequest();
	this->FindComponentByClass<UUnitGathererComponent>()->ClearGatherRequest();

	Super::StopAllActions();
}