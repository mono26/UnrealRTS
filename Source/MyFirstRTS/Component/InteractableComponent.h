// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	float InteractableRadius;

public:
	// Sets default values for this component's properties
	UInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	USceneComponent* GetClosestInteractionPointTo(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	float GetInteractableRadius();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void SetInteractableRadius(float Radius);
};
