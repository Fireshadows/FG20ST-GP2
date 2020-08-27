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
	bool Clickable();
	virtual bool Clickable_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool Draggable();
	virtual bool Draggable_Implementation() override;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Click();
	void Click_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Drag(FVector MouseLocation);
	void Drag_Implementation(FVector MouseLocation) override;

};
