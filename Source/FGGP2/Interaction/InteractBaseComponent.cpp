// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractBaseComponent.h"

// Sets default values for this component's properties
UInteractBaseComponent::UInteractBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

bool UInteractBaseComponent::Draggable_Implementation()
{
	return interactable;
}

void UInteractBaseComponent::Drag_Implementation(FVector MouseLocation)
{

}

void UInteractBaseComponent::Click_Implementation()
{

}

bool UInteractBaseComponent::Clickable_Implementation()
{
	return interactable;
}

