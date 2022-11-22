// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "../Resource/ResourceComponent.h"
#include "../Unit/UnitComponent.h"
#include "../Unit/Command/UnitCommand.h"
#include "WorkerUnit.generated.h"

DECLARE_DYNAMIC_DELEGATE(FVoidSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetChangedSignature, const AActor*, OldTarget, const AActor*, NewTarget);

struct FMovementRequest
{
public:
	uint32 requestId;

	FVoidSignature OnSuccess;
	FVoidSignature OnFail;

	FMovementRequest()
	{

	}

	FMovementRequest(int requestId, FVoidSignature OnSuccess, FVoidSignature OnFail)
	{
		this->requestId = requestId;
		this->OnSuccess = OnSuccess;
		this->OnFail = OnFail;
	}
};

struct FTimerWithCallback
{
private:
	FVoidSignature OnSuccess;
	FVoidSignature OnFail;

	FTimerHandle TimerHandle;
	FTimerManager TimerManager;

public:
	FTimerWithCallback()
	{

	}

	FTimerWithCallback(float Time, FVoidSignature OnSuccess, FVoidSignature OnFail)
	{
		this->OnSuccess = OnSuccess;
		this->OnFail = OnFail;

		this->TimerManager.SetTimer(this->TimerHandle, [&]() {
			OnSuccess.ExecuteIfBound();
			// TODO delete this?
			}, Time, false);
	}

	void Stop()
	{
		this->TimerManager.ClearTimer(this->TimerHandle);
		this->OnFail.ExecuteIfBound();
	}
};

UCLASS()
class MYFIRSTRTS_API AWorkerUnit : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Worker")
	FTargetChangedSignature OnTargetChanged;

private:
	UUnitComponent* UnitComponent = nullptr;

	AActor* AttackTargetRef = nullptr;

	TMap<uint32, FMovementRequest> MovementRequest;

	uint32 CarriedResourceAmount = 0;
	EResourceType CarriedResource = EResourceType::None;
	FTimerWithCallback* GatherTimer;
	AActor* TargetResourceRef = nullptr;

public:
	// Sets default values for this character's properties
	AWorkerUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	AActor* GetAttackTarget();

	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	void SetAttackTarget(AActor* AttackTarget);

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToPosition(FVector Position, FVoidSignature OnSuccess, FVoidSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToActor(AActor* ActorRef, FVoidSignature OnSuccess, FVoidSignature OnFail);

	void OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker|Movement")
	void OnStartMovement();

	UFUNCTION(BlueprintCallable, Category = "Worker|Gathering")
	AActor* GetResource();

	UFUNCTION(BlueprintCallable, Category = "Worker|Gathering")
	void SetTargetResource(AActor* Resource);

	void ExtractResource(AActor* ResourceRef, FVoidSignature OnSuccess, FVoidSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "Worker|Commands")
	void ExecuteCommand(UUnitCommand* Command);

	UFUNCTION(BlueprintCallable, Category = "Worker")
	void StopAllActions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker")
	void OnStopAll();
};
