// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"

UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent))
class FGGP2_API UInventory : public UActorComponent
{
	GENERATED_BODY()

	/** Dummy root component */
	//UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class USceneComponent* DummyRoot;
		
public:	
	// Sets default values for this actor's properties
	UInventory();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int InventorySize = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> Inventory;

	UFUNCTION(BlueprintCallable)
	bool AddItem(AActor* InventoryItem);
	UFUNCTION(BlueprintCallable)
	void RemoveItem();

	UFUNCTION(BlueprintCallable)
	int ItemCount();

	UFUNCTION(BlueprintCallable)
	bool IsNotFull();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickfunction) override;

	/** Returns DummyRoot subobject **/
	//FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

};
