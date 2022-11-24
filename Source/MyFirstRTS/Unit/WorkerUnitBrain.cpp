// Copyright: For learning purposes, Mono Zubiria.


#include "WorkerUnitBrain.h"
#include "WorkerUnit.h"
#include "UnitComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../Building/BuildingComponent.h"
#include "../Component/TeamComponent.h"
#include "../Game/MyFirstRTSGameMode.h"

// Sets default values for this component's properties
UWorkerUnitBrain::UWorkerUnitBrain()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->PerceptionComponent = nullptr;
}


// Called when the game starts
void UWorkerUnitBrain::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* owner = this->GetOwner();
	this->PerceptionComponent = owner->FindComponentByClass<UAIPerceptionComponent>();
}


// Called every frame
void UWorkerUnitBrain::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UWorkerUnitBrain::GetNextTargetInSight()
{
	if (this->PerceptionComponent == nullptr) {
		return nullptr;
	}

	TArray<AActor*> possibleTargets;
	this->PerceptionComponent->GetPerceivedHostileActorsBySense(UAISense_Sight::StaticClass(), possibleTargets);
	if (possibleTargets.IsEmpty()) {
		return nullptr;
	}

	AActor* targetRef = nullptr;
	for (AActor* actor : possibleTargets) {
		if (!this->IsFromTheSameTeam(actor)) {
			continue;
		}

		if (targetRef == nullptr) {
			targetRef = actor;
			continue;
		}

		if (targetRef->GetComponentByClass(UUnitComponent::StaticClass()) != nullptr && actor->GetComponentByClass(UUnitComponent::StaticClass()) != nullptr) {
			targetRef = this->SelectClosestActor(targetRef, actor);
		}
		else if (targetRef->GetComponentByClass(UBuildingComponent::StaticClass()) != nullptr) {
			if (actor->GetComponentByClass(UUnitComponent::StaticClass()) != nullptr) {
				targetRef = actor;
			}
			else if (actor->GetComponentByClass(UBuildingComponent::StaticClass()) != nullptr) {
				targetRef = this->SelectClosestActor(targetRef, actor);
			}
		}
	}

	return targetRef;
}

void UWorkerUnitBrain::OnSightUpdated(AActor* Instigator)
{
	if (Instigator == nullptr) {
		return;
	}

	if (this->IsFromTheSameTeam(Instigator)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't target the same team."));
		return;
	}

	AAIController* ownerController = Cast<AAIController>(this->GetOwner());
	AWorkerUnit* asWorker = Cast<AWorkerUnit>(ownerController->GetPawn());

	UUnitComponent* unitComponent = ownerController->GetPawn()->FindComponentByClass<UUnitComponent>();

	if (asWorker == nullptr || unitComponent == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Actor is not a valid worker."));
		return;
	}

	AActor* currentTarget = asWorker->GetAttackTarget();
	if (currentTarget == nullptr) {
		asWorker->SetAttackTarget(Instigator);
		return;
	}

	if (currentTarget == Instigator) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Shouldn't target the same target twice."));
		return;
	}

	if (currentTarget->GetComponentByClass(UUnitComponent::StaticClass()) != nullptr && Instigator->GetComponentByClass(UUnitComponent::StaticClass()) != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Select closest unit."));
		asWorker->SetAttackTarget(this->SelectClosestActor(currentTarget, Instigator));
	}
	else if (currentTarget->GetComponentByClass(UBuildingComponent::StaticClass()) != nullptr) {
		// Units have priority over buildings.
		if (Instigator->GetComponentByClass(UUnitComponent::StaticClass()) != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Target unit."));
			asWorker->SetAttackTarget(Instigator);
		}
		else if (Instigator->GetComponentByClass(UBuildingComponent::StaticClass()) != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Select closest building."));
			asWorker->SetAttackTarget(this->SelectClosestActor(currentTarget, Instigator));
		}
	}
}

AActor* UWorkerUnitBrain::GetPlayerTownhall()
{
	UWorld* world = this->GetWorld();
	AGameModeBase* gameMode = world->GetAuthGameMode();
	AMyFirstRTSGameMode* rtsMode = Cast<AMyFirstRTSGameMode>(gameMode);
	if (rtsMode == nullptr) {
		return nullptr;
	}

	return rtsMode->GetPlayerTownhall();
}

bool UWorkerUnitBrain::IsFromTheSameTeam(AActor* OtherRef)
{
	UTeamComponent* teamComponent = this->GetOwner()->FindComponentByClass<UTeamComponent>();
	if (OtherRef == nullptr || teamComponent == nullptr) {
		return false;
	}

	UTeamComponent* otherTeamComponent = OtherRef->FindComponentByClass<UTeamComponent>();
	if (otherTeamComponent != nullptr) {
		return teamComponent->TeamAttitude.GetValue() == otherTeamComponent->TeamAttitude.GetValue();
	}

	return false;
}

AActor* UWorkerUnitBrain::SelectClosestActor(AActor* ActorARef, AActor* ActorBRef)
{
	if (ActorARef == nullptr) {
		return ActorBRef;
	}
	else if (ActorBRef == nullptr) {
		return ActorARef;
	}
	else if (ActorARef == nullptr && ActorBRef == nullptr) {
		return nullptr;
	}

	AActor* owner = this->GetOwner();
	FVector ownerLocation = owner->GetActorLocation();

	FVector aLocation = ActorARef->GetActorLocation();
	FVector bLocation = ActorBRef->GetActorLocation();

	float sqrDistanceToA = FVector::DistSquared(ownerLocation, aLocation);
	float sqrDistanceToB = FVector::DistSquared(ownerLocation, bLocation);

	return sqrDistanceToA < sqrDistanceToB ? ActorARef : ActorBRef;
}

