// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Unit/Command/UnitCommand.h"
#include "../Resource/ResourceComponent.h"
#include "HealthComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FMulticastActionSignature OnHealthZero;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	FVector HealthBarLocalPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	FVector2D HealthBarSize;

private:
	int HealthCurrent;
	int HealthMax;

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	int GetHealthCurrent() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	int GetMaxHealth() const;

	void InitializeHealthValues(int HealthValue);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnDamage(int DamageTaken);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Health")
	void UpdateHealthBar();
};
