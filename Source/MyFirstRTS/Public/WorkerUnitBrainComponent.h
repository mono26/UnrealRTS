// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "WorkerUnitBrainComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTRTS_API UWorkerUnitBrainComponent : public UActorComponent
{
public:
	UAIPerceptionComponent* PerceptionComponent;

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWorkerUnitBrainComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetNextTargetInSight();

	AActor* GetPlayerTownhall();

	void OnTargetChanged();

	void OnSightUpdated(AActor* Instigator);

	AActor* SelectClosestActor(AActor* ActorARef, AActor* ActorBRef);
};
