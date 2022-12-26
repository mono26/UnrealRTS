// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "../Unit/Component/UnitComponent.h"
#include "../Unit/Command/UnitCommand.h"
#include "../Component/FactionCommander.h"
#include "RTSUnit.generated.h"

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
class MYFIRSTRTS_API ARTSUnit : public ACharacter
{
	GENERATED_BODY()

private:
	bool bIsRunningCommand = false;

	UFactionCommander* OwnerCommander = nullptr;

	UUnitComponent* UnitComponent = nullptr;

public:
	// Sets default values for this character's properties
	ARTSUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UUnitComponent* GetUnitComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|Commands")
	void ExecuteCommand(UUnitCommand* Command);

	UFUNCTION(BlueprintCallable, Category = "Unit|Commands")
	bool GetIsRunningCommand();

	UFUNCTION(BlueprintCallable, Category = "Unit|General")
	UFactionCommander* GetOwnerCommander() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|General")
	void SetOwnerCommander(UFactionCommander* Commander);

	UFUNCTION(BlueprintCallable, Category = "Unit|General")
	virtual void StopAllActions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Unit|General")
	void OnStopAll();
};
