// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Component/CommanderComponent.h"
#include "../Component/FactionCommander.h"
#include "EnemyCommander.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UEnemyCommander : public UFactionCommander
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Spawn")
	bool bInfiniteWaves = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Spawn")
	float TimeBetweenWaves = 1;

private:
	FTimerHandle SpawnTimerHandle;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Enemy|Spawn")
	void OnSpawnEnemy(AActor* Enemy);

	UFUNCTION(BlueprintCallable, Category = "Enemy|Spawn")
	void StartSpawn();
};
