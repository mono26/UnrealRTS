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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetChangedSignature, const AActor*, OldTarget, const AActor*, NewTarget);

struct FMovementRequest
{
public:
	uint32 requestId;

	FActionSignature OnSuccess;
	FActionSignature OnFail;

	FMovementRequest()
	{

	}

	FMovementRequest(int requestId, FActionSignature OnSuccess, FActionSignature OnFail)
	{
		this->requestId = requestId;
		this->OnSuccess = OnSuccess;
		this->OnFail = OnFail;
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
	FExtendedTimer()
	{

	}

	FExtendedTimer(FTimerManager* Manager, float Time, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
	{
		this->TimerManager = Manager;

		this->OnSuccess = OnSuccessCallback;
		this->OnFail = OnFailCallback;

		this->TimerManager->SetTimer(this->TimerHandle, [&]() {
			this->OnSuccess.ExecuteIfBound();
			// TODO delete this?
			}, Time, false);
	}

	void Stop()
	{
		this->TimerManager->ClearTimer(this->TimerHandle);
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	EResourceType CarriedResource = EResourceType::None;

private:
	UUnitComponent* UnitComponent = nullptr;

	AActor* AttackTargetRef = nullptr;

	TMap<uint32, FMovementRequest> MovementRequest;

	uint32 CarriedResourceAmount = 0;
	FExtendedTimer* GatherTimer;
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
	void MoveToPosition(FVector Position, FActionSignature OnSuccess, FActionSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToActor(AActor* ActorRef, FActionSignature OnSuccess, FActionSignature OnFail);

	void OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker|Movement")
	void OnStartMovement();

	UFUNCTION(BlueprintCallable, Category = "Worker|Gathering")
	AActor* GetResource();

	UFUNCTION(BlueprintCallable, Category = "Worker|Gathering")
	void SetTargetResource(AActor* Resource);

	void ExtractResource(AActor* ResourceRef, FActionSignature OnSuccess, FActionSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "Worker|Commands")
	void ExecuteCommand(UUnitCommand* Command);

	UFUNCTION(BlueprintCallable, Category = "Worker")
	void StopAllActions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker")
	void OnStopAll();
};
