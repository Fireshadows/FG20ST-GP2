// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SubtitleTextData.h"
#include "SubtitleInterface.h"
#include "../Interaction/InteractBaseComponent.h"
#include "SubtitleComponent.generated.h"

UENUM(BlueprintType)
enum ESubtitleEvent
{
	SubtitleFinished,
	SubtitleStarted,
	SubtitleNext
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSubtitleDelegate, ESubtitleEvent, SubtitleEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGGP2_API USubtitleComponent : public UInteractBaseComponent, public ISubtitleInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USubtitleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Subtitles")
	USubtitleDataAsset* DataAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Subtitles")
	int index;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Subtitles")
	void Clicked();
	virtual void Clicked_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	void Next();
	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	void Start();
	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	void Ended();

	UPROPERTY(BlueprintAssignable, Category = "Subtitles")
	FSubtitleDelegate SubtitleEvent;

	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	FTextData GetCurrentTextData();

	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	void StartTimer(float duration);

	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	void StopTimer();

private:
	

	FTimerHandle ShowNextSubtitleTimerHandle;




		
};
