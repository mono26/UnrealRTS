// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "WorkerUnitBrain.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UWorkerUnitBrain : public UActorComponent
{
	GENERATED_BODY()

public:
	UAIPerceptionComponent* PerceptionComponent;

public:
	// Sets default values for this component's properties
	UWorkerUnitBrain();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "WorkerBrain")
	AActor* GetNextTargetInSight();

	UFUNCTION(BlueprintCallable, Category = "WorkerBrain") 
	AActor* GetPlayerTownhall();

	bool IsFromTheSameTeam(AActor* OtherRef);

	UFUNCTION(BlueprintCallable, Category = "WorkerBrain")
	void OnSightUpdated(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category = "WorkerBrain")
	AActor* SelectClosestActor(AActor* ActorARef, AActor* ActorBRef);
};
