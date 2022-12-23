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
#include "../Component/FactionCommander.h"
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

	~FExtendedTimer()
	{
		this->TimerManager = nullptr;
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

private:
	bool bIsRunningCommand = false;

	UFactionCommander* OwnerCommander = nullptr;

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

	UFUNCTION(BlueprintCallable, Category = "Worker")
	UFactionCommander* GetOwnerCommander() const;

	UFUNCTION(BlueprintCallable, Category = "Worker")
	void SetOwnerCommander(UFactionCommander* Commander);

	UFUNCTION(BlueprintCallable, Category = "Worker")
	void StopAllActions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker")
	void OnStopAll();
};
