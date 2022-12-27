// Copyright: For learning purposes, Mono Zubiria.


#include "UnitGathererComponent.h"
#include "../../Player/PlayerCommander.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UUnitGathererComponent::UUnitGathererComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->GatherRequest = new FGatherRequest();
	this->GatherTimer = nullptr;

	this->OnExtractResourceDelegate.BindUFunction(this, FName("OnExtractResource"));
}

// Called when the game starts
void UUnitGathererComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UUnitGathererComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUnitGathererComponent::ClearGatherRequest()
{
	this->SetGatherRequest(FGatherRequest());

	if (this->GatherTimer != nullptr) {
		FExtendedTimer timer = *this->GatherTimer;

		this->GatherTimer = nullptr;

		timer.Stop();
	}
}

AActor* UUnitGathererComponent::GetTargetResource() const
{
	return this->GatherRequest != nullptr ? this->GatherRequest->GetResourceRef() : nullptr;
}

void UUnitGathererComponent::SetGatherRequest(FGatherRequest Request)
{
	this->GatherRequest->SetResourceRef(Request.GetResourceRef());
	this->GatherRequest->SetOnSuccess(Request.GetOnSuccess());
	this->GatherRequest->SetOnFail(Request.GetOnFail());

	// TODO trigger on resource changed.
}

void UUnitGathererComponent::ExtractResource()
{
	if (this->GetTargetResource() == nullptr) {
		this->GatherRequest->GetOnFail().ExecuteIfBound();
		return;
	}

	UResourceComponent* resourceComponent = this->GatherRequest->GetResourceRef()->FindComponentByClass<UResourceComponent>();
	if (resourceComponent == nullptr) {
		this->GatherRequest->GetOnFail().ExecuteIfBound();
		return;
	}

	if (this->CarriedResource.ResourceType == resourceComponent->ResourceType) {
		UE_LOG(LogTemp, Warning, TEXT("Already have this resource."));
		this->GatherRequest->GetOnSuccess().ExecuteIfBound();
		return;
	}

	if (!resourceComponent->CanGather()) {
		this->GatherRequest->GetOnFail().ExecuteIfBound();
		return;
	}

	this->GatherTimer = new FExtendedTimer(&this->GetWorld()->GetTimerManager(), 3.0f, this->OnExtractResourceDelegate, this->GatherRequest->GetOnFail());

	this->GetOwner()->FindComponentByClass<UUnitComponent>()->SetCurrentState(EUnitStates::Gathering);
}

void UUnitGathererComponent::OnExtractResource()
{
	if (this->GetTargetResource() == nullptr) {
		this->GatherRequest->GetOnFail().ExecuteIfBound();
		return;
	}

	UResourceComponent* resourceComponent = this->GetTargetResource()->FindComponentByClass<UResourceComponent>();
	if (resourceComponent == nullptr) {
		this->GatherRequest->GetOnFail().ExecuteIfBound();
		return;
	}

	this->CarriedResource = resourceComponent->GetGatheredResource();

	this->GatherRequest->GetOnSuccess().ExecuteIfBound();
}

void UUnitGathererComponent::StoreResource()
{
	if (this->CarriedResource.ResourceType == EResourceType::None || this->CarriedResource.ResourceAmount <= 0) {
		return;
	}

	APlayerCommander* commander = Cast<APlayerCommander>(UGameplayStatics::GetPlayerController(this, 0));
	commander->ReceiveResources(this->CarriedResource.ResourceType, this->CarriedResource.ResourceAmount);
	// TODO delete old resource? Or maybe just create a pointer and set the inner values.
	this->CarriedResource = FResource();
}

void UUnitGathererComponent::StopAction()
{
	this->ClearGatherRequest();
}