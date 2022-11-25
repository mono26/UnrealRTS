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
	FGatherRequest()
	{

	}

	FGatherRequest(AActor* Resource, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
	{
		this->ResourceRef = Resource;

		this->OnSuccess = OnSuccessCallback;
		this->OnFail = OnFailCallback;
	}

	AActor* GetResourceRef()
	{
		return this->ResourceRef;
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetChangedSignature, const AActor*, OldTarget, const AActor*, NewTarget);

UCLASS()
class MYFIRSTRTS_API AWorkerUnit : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Worker")
	FTargetChangedSignature OnTargetChangedEvent;

	FActionSignature OnExtractResourceDelegate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Worker")
	FResource CarriedResource;

private:
	UUnitComponent* UnitComponent = nullptr;

	AActor* AttackTargetRef = nullptr;

	TMap<uint32, FMovementRequest> MovementRequest;

	FGatherRequest GatherRequest;
	FExtendedTimer* GatherTimer;

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
	void MoveToPosition(FVector Position, FActionSignature OnSuccess, FActionSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToActor(AActor* ActorRef, FActionSignature OnSuccess, FActionSignature OnFail);

	void OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker|Movement")
	void OnStartMovement();

	UFUNCTION(BlueprintCallable, Category = "Worker|Gathering")
	AActor* GetTargetResource();

	void SetGatherRequest(FGatherRequest Request);

	void ExtractResource(/*AActor* ResourceRef, FActionSignature OnSuccess, FActionSignature OnFail*/);

	UFUNCTION()
	void OnExtractResource();

	void StoreResource();

	UFUNCTION(BlueprintCallable, Category = "Worker|Commands")
	void ExecuteCommand(UUnitCommand* Command);

	UFUNCTION(BlueprintCallable, Category = "Worker")
	void StopAllActions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker")
	void OnStopAll();
};
