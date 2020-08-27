// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubtitleTextData.generated.h"


USTRUCT(BlueprintType)
struct FTextData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text")
	FText line;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text")
	float duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text")
	bool interactable;
};

/**
 * 
 */

UCLASS(BlueprintType)
class FGGP2_API USubtitleDataAsset : public UDataAsset
{
public:
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text")
	TArray<FTextData> texts;
};