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
#include "../Component/CommanderComponent.h"
#include "WorkerUnit.generated.h"

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

//struct FAttackRequest
//{
//private:
//	float DistanceToTarget;
//
//	AActor* AttackTargetRef;
//
//	FActionSignature OnSuccess;
//	FActionSignature OnFail;
//
//public:
//	FAttackRequest() : FAttackRequest(nullptr, FActionSignature(), FActionSignature())
//	{
//
//	}
//
//	FAttackRequest(AActor* AttackTarget, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
//	{
//		this->AttackTargetRef = AttackTarget;
//
//		this->OnSuccess = OnSuccessCallback;
//		this->OnFail = OnFailCallback;
//	}
//
//	AActor* GetAttackTargetRef() const
//	{
//		return this->AttackTargetRef;
//	}
//
//	FActionSignature GetOnSuccess() const
//	{
//		return this->OnSuccess;
//	}
//
//	FActionSignature GetOnFail() const
//	{
//		return this->OnFail;
//	}
//
//	float GetDistanceToTarget() const
//	{
//		return this->DistanceToTarget;
//	}
//
//	void SetDistanceToTarget(float Distance)
//	{
//		this->DistanceToTarget = Distance;
//	}
//
//	void SetAttackTargetRef(AActor* AttackTarget)
//	{
//		this->AttackTargetRef = AttackTarget;
//	}
//
//	void SetOnSuccess(FActionSignature OnSuccessCallback)
//	{
//		this->OnSuccess = OnSuccessCallback;
//	}
//
//	void SetOnFail(FActionSignature OnFailCallback)
//	{
//		this->OnFail = OnFailCallback;
//	}
//};

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetChangedSignature, const AActor*, OldTarget, const AActor*, NewTarget);

UCLASS()
class MYFIRSTRTS_API AWorkerUnit : public ACharacter
{
	GENERATED_BODY()

private:
	bool bIsRunningCommand = false;

	UCommanderComponent* OwnerCommander = nullptr;

	UUnitComponent* UnitComponent = nullptr;

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
	UFUNCTION(BlueprintCallable, Category = "Worker|Commands")
	void ExecuteCommand(UUnitCommand* Command);

	UFUNCTION(BlueprintCallable, Category = "Worker|Commands")
	bool GetIsRunningCommand();

	UUnitComponent* GetUnitComponent() const;

	UCommanderComponent* GetOwnerCommander() const;

	void SetOwnerCommander(UCommanderComponent* Commander);

	UFUNCTION(BlueprintCallable, Category = "Worker")
	void StopAllActions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker")
	void OnStopAll();
};
