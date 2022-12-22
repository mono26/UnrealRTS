// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Unit/Command/UnitCommand.h"
#include "CommanderComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UCommanderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCommanderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	void ExecuteAttackCommand(AActor* AttackTarget, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	void ExecuteGatherCommand(AActor* Resource, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	void ExecuteMovementCommand(FVector TargetPosition, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	void ExecuteStopCommand(AActor* UnitRef);

	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Command")
	void ExecuteStoreCommand(AActor* Storage, AActor* UnitRef, FActionSignature OnSuccess, FActionSignature OnFail);

	void OnExecuteMoveSuccess();

	void OnExecuteMoveFail();
};
