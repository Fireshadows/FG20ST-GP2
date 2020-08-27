#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class FGGP2_API IInteractInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool Clickable();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool Draggable();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Click();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Drag(FVector MouseLocation);

};
