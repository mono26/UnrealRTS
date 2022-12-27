// Copyright: For learning purposes, Mono Zubiria.


#include "WorkerUnitBrain.h"
#include "UnitComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../../Building/BuildingComponent.h"
#include "../../Component/TeamComponent.h"
#include "../../Game/MyFirstRTSGameMode.h"
#include "UnitAttackComponent.h"
#include "UnitGathererComponent.h"
#include "../../Component/HealthComponent.h"

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

		UHealthComponent* healthComponent = actor->FindComponentByClass<UHealthComponent>();
		if (healthComponent->GetHealthCurrent() <= 0) {
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

bool UWorkerUnitBrain::IsCloserThanCurrentTarget(AActor* OtherRef)
{
	if (OtherRef == nullptr) {
		return false;
	}

	AAIController* ownerController = Cast<AAIController>(this->GetOwner());
	AActor* currentTarget = ownerController->GetPawn()->FindComponentByClass<UUnitAttackComponent>()->GetAttackTarget();
	if (currentTarget == nullptr) {
		return true;
	}

	AActor* closestActor = this->SelectClosestActor(currentTarget, OtherRef);

	return closestActor == OtherRef;
}

bool UWorkerUnitBrain::IsFromTheSameTeam(AActor* OtherRef)
{
	if (OtherRef == nullptr) {
		return true;
	}

	AAIController* ownerController = Cast<AAIController>(this->GetOwner());
	UTeamComponent* teamComponent = ownerController->GetPawn()->FindComponentByClass<UTeamComponent>();
	if (teamComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("I, %s, don't have a team component."), *ownerController->GetPawn()->GetName());
		return true;
	}

	UTeamComponent* otherTeamComponent = OtherRef->FindComponentByClass<UTeamComponent>();
	if (otherTeamComponent != nullptr) {
		return teamComponent->TeamAttitude.GetValue() == otherTeamComponent->TeamAttitude.GetValue();
	}

	return true;
}

bool UWorkerUnitBrain::IsGatheringResource()
{
	AAIController* ownerController = Cast<AAIController>(this->GetOwner());
	UUnitGathererComponent* gatherComponent = ownerController->GetPawn()->FindComponentByClass<UUnitGathererComponent>();
	if (gatherComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("I, %s, don't have a gather component."), *ownerController->GetPawn()->GetName());
		return true;
	}

	return gatherComponent->GetTargetResource() != nullptr;
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

