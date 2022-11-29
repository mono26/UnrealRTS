// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "EnemySpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemySpawnSignature, const AActor*, Enemy);

UCLASS()
class MYFIRSTRTS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Worker|Target")
	FEnemySpawnSignature OnSpawnEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Spawn")
	int MinSpawnPerWave = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Spawn")
	int MaxSpawnPerWave = 1;

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy|Spawn")
	FVector GetSpawnPosition();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy|Spawn")
	AActor* SpawnEnemy(FVector SpawnPosition);

	UFUNCTION(BlueprintCallable, Category = "Enemy|Spawn")
	void SpawnWave();
};
