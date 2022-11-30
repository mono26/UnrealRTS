// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "AIController.h"
#include "Components/ActorComponent.h"
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
class MYFIRSTRTS_API UUnitComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnStateChangedSignature, UUnitComponent, OnCurrentStateChanged);

public:
	UPROPERTY(BlueprintAssignable, Category = "Unit")
	FOnStateChangedSignature OnCurrentStateChanged;

	// TODO move current health to it's own component.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Health")
	float HealthCurrent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Health")
	float HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Health")
	FVector HealthBarLocalPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Health")
	FVector2D HealthBarSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Attack")
	float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Attack")
	float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit|Attack")
	float AttackSwingDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FVector UnitCenter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float UnitSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
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
};
