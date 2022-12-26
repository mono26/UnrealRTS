// Copyright: For learning purposes, Mono Zubiria.


#include "RangedUnit.h"
#include "Component/UnitAttackComponent.h"

void ARangedUnit::StopAllActions()
{
	this->FindComponentByClass<UUnitAttackComponent>()->ClearAttackRequest();

	Super::StopAllActions();
}