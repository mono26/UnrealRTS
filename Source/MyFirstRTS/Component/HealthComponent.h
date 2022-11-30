// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Health")
	FVector HealthBarLocalPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Health")
	FVector2D HealthBarSize;

private:
	float HealthCurrent;
	float HealthMax;

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
	void GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnDamage(float DamageTake);

	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void UpdateHealthBar();
};
