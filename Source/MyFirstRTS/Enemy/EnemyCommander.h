// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Component/CommanderComponent.h"
#include "EnemyCommander.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UEnemyCommander : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Spawn")
	bool bInfiniteWaves = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Spawn")
	float TimeBetweenWaves = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy|Command")
	UCommanderComponent* CommandComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	TArray<AActor*> ActiveEnemies;

private:
	FTimerHandle SpawnTimerHandle;

public:	
	// Sets default values for this component's properties
	UEnemyCommander();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "WorkerBrain")
	AActor* GetPlayerTownhall();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Enemy|Spawn")
	void OnSpawnEnemy(AActor* Enemy);

	UFUNCTION(BlueprintCallable, Category = "Enemy|Spawn")
	void StartSpawn();
};
