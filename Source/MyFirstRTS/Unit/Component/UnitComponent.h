// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "AIController.h"
#include "Components/ActorComponent.h"
#include "UnitComponentInterface.h"
#include "UnitComponent.generated.h"

UENUM(BlueprintType)
enum class EUnitStates : uint8
{
	None,
	Idle,
	Moving,
	Gathering,
	Attacking
};

UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UUnitComponent : public UActorComponent, public IUnitComponentInterface
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnStateChangedSignature, UUnitComponent, OnCurrentStateChanged);

	UPROPERTY(BlueprintAssignable, Category = "Unit")
	FOnStateChangedSignature OnCurrentStateChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit|Health")
	int HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit|Attack")
	int AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit|Attack")
	float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit|Attack")
	float AttackSwingDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
	FVector UnitCenter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
	float UnitSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
	float VisionRange;

private:
	EUnitStates CurrentState;

public:	
	// Sets default values for this component's properties
	UUnitComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Unit|State")
	EUnitStates GetCurrentState();

	UFUNCTION(BlueprintCallable, Category = "Unit|State")
	void SetCurrentState(EUnitStates NewState);

	void StopAction() override;
};
