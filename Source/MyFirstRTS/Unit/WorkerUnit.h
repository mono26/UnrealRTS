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

struct FMovementRequest
{
private:
	uint32 RequestId;

	FActionSignature OnSuccess;
	FActionSignature OnFail;

public:
	FMovementRequest() : FMovementRequest(0, FActionSignature(), FActionSignature())
	{

	}

	FMovementRequest(int requestId, FActionSignature OnSuccess, FActionSignature OnFail)
	{
		this->RequestId = requestId;
		this->OnSuccess = OnSuccess;
		this->OnFail = OnFail;
	}

	uint32 GetResquestId()
	{
		return this->RequestId;
	}

	FActionSignature GetOnSuccess()
	{
		return this->OnSuccess;
	}

	FActionSignature GetOnFail()
	{
		return this->OnFail;
	}
};

struct FExtendedTimer
{
private:
	FActionSignature OnSuccess;
	FActionSignature OnFail;

	FTimerHandle TimerHandle;
	FTimerManager* TimerManager;

public:
	FExtendedTimer() : FExtendedTimer(nullptr, 0.0f, FActionSignature(), FActionSignature())
	{

	}

	FExtendedTimer(FTimerManager* Manager, float Time, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
	{
		this->TimerManager = Manager;

		this->OnSuccess = OnSuccessCallback;
		this->OnFail = OnFailCallback;

		this->TimerManager->SetTimer(this->TimerHandle, [&]() {
			this->OnSuccess.Execute();
			// TODO delete this?
			}, Time, false);
	}

	void Stop()
	{
		this->TimerManager->ClearTimer(this->TimerHandle);
		this->OnFail.ExecuteIfBound();
	}
};

struct FGatherRequest
{
private:
	AActor* ResourceRef;

	FActionSignature OnSuccess;
	FActionSignature OnFail;

public:
	FGatherRequest() : FGatherRequest(nullptr, FActionSignature(), FActionSignature())
	{

	}

	FGatherRequest(AActor* Resource, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
	{
		this->ResourceRef = Resource;

		this->OnSuccess = OnSuccessCallback;
		this->OnFail = OnFailCallback;
	}

	AActor* GetResourceRef() const
	{
		return this->ResourceRef;
	}

	FActionSignature GetOnSuccess() const
	{
		return this->OnSuccess;
	}

	FActionSignature GetOnFail() const
	{
		return this->OnFail;
	}

	void SetResourceRef(AActor* Resource)
	{
		this->ResourceRef = Resource;
	}

	void SetOnSuccess(FActionSignature OnSuccessCallback)
	{
		this->OnSuccess = OnSuccessCallback;
	}

	void SetOnFail(FActionSignature OnFailCallback)
	{
		this->OnFail = OnFailCallback;
	}
};

struct FAttackRequest
{
private:
	float DistanceToTarget;

	AActor* AttackTargetRef;

	FActionSignature OnSuccess;
	FActionSignature OnFail;

public:
	FAttackRequest() : FAttackRequest(nullptr, FActionSignature(), FActionSignature())
	{

	}

	FAttackRequest(AActor* AttackTarget, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
	{
		this->AttackTargetRef = AttackTarget;

		this->OnSuccess = OnSuccessCallback;
		this->OnFail = OnFailCallback;
	}

	AActor* GetAttackTargetRef() const
	{
		return this->AttackTargetRef;
	}

	FActionSignature GetOnSuccess() const
	{
		return this->OnSuccess;
	}

	FActionSignature GetOnFail() const
	{
		return this->OnFail;
	}

	float GetDistanceToTarget() const
	{
		return this->DistanceToTarget;
	}

	void SetDistanceToTarget(float Distance)
	{
		this->DistanceToTarget = Distance;
	}

	void SetAttackTargetRef(AActor* AttackTarget)
	{
		this->AttackTargetRef = AttackTarget;
	}

	void SetOnSuccess(FActionSignature OnSuccessCallback)
	{
		this->OnSuccess = OnSuccessCallback;
	}

	void SetOnFail(FActionSignature OnFailCallback)
	{
		this->OnFail = OnFailCallback;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetChangedSignature, const AActor*, OldTarget, const AActor*, NewTarget);

UCLASS()
class MYFIRSTRTS_API AWorkerUnit : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Worker|Target")
	FTargetChangedSignature OnTargetChangedEvent;

	UPROPERTY(BlueprintReadOnly, Category = "Worker|Gathering")
	FResource CarriedResource;

private:
	bool bIsRunningCommand = false;

	UUnitComponent* UnitComponent = nullptr;

	FAttackRequest* AttackRequest;
	FExtendedTimer* AttackTimer;
	FActionSignature OnExecuteAttackDelegate;

	TMap<uint32, FMovementRequest> MovementRequest;

	FGatherRequest* GatherRequest;
	FExtendedTimer* GatherTimer;
	FActionSignature OnExtractResourceDelegate;

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
	void ExecuteAttack();

	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	void ClearAttackRequest();

	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	AActor* GetAttackTarget() const;

	void SetAttackRequest(FAttackRequest Request);

	UFUNCTION()
	void OnExecuteAttack();

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToPosition(FVector Position, FActionSignature OnSuccess, FActionSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToActor(AActor* ActorRef, FActionSignature OnSuccess, FActionSignature OnFail);

	void OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker|Movement")
	void OnStartMovement();

	UFUNCTION(BlueprintCallable, Category = "Worker|Gathering")
	AActor* GetTargetResource() const;

	void ExtractResource();

	UFUNCTION()
	void OnExtractResource();

	void SetGatherRequest(FGatherRequest Request);

	void StoreResource();

	UFUNCTION(BlueprintCallable, Category = "Worker|Commands")
	void ExecuteCommand(UUnitCommand* Command);

	UFUNCTION(BlueprintCallable, Category = "Worker|Commands")
	bool GetIsRunningCommand();

	UFUNCTION(BlueprintCallable, Category = "Worker")
	void StopAllActions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker")
	void OnStopAll();
};
