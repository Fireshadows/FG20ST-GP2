// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractInterface.h"
#include "InteractBaseComponent.generated.h"


UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGGP2_API UInteractBaseComponent : public UActorComponent, public IInteractInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractBaseComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interact")
	bool interactable = true;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Clickable();
	virtual void Clickable_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Draggable(FVector MouseLocation);
	virtual void Draggable_Implementation(FVector MouseLocation) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Interact(FVector MouseLocation);
	virtual void Interact_Implementation(FVector MouseLocation) override;




public:

};
