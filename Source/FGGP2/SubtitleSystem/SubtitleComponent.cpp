#include "SubtitleComponent.h"

USubtitleComponent::USubtitleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	index = 0;

}

void USubtitleComponent::BeginPlay()
{
	Super::BeginPlay();

}

void USubtitleComponent::Clicked_Implementation()
{
	if (DataAsset == nullptr)
	{
		return;
	}
	if (DataAsset->texts.Num() > 0)
	{
		auto currentTextData = GetCurrentTextData();
		switch (currentTextData.triggerType)
		{
		case ENextLineTrigger::OnClick:
		{

		}break;
		case ENextLineTrigger::OnFixedDuration:
		{
			return;
		}break;
		case ENextLineTrigger::OnFixedDurationOrClick:
		{
			StopTimer();
		}break;
		case ENextLineTrigger::OnTriggerEnter:
		{
			return;
		}break;
		}
	}

	if (index == 0)
	{
		Start();
	}
	else
	{
		Next();
	}
}

void USubtitleComponent::Next()
{
	if (index < DataAsset->texts.Num())
	{
		currentText.duration = DataAsset->texts[index].duration;
		currentText.soundRef = DataAsset->texts[index].soundRef;
		currentText.line = DataAsset->texts[index].line;
		currentText.triggerType = DataAsset->texts[index].triggerType;
		SubtitleEvent.Broadcast(ESubtitleEvent::SubtitleNext);
		index++;
	}
	else
	{
		Ended();
	}

}	
void USubtitleComponent::Start()
{
	if (DataAsset)
	{
		if (index < DataAsset->texts.Num())
		{
			currentText.duration = DataAsset->texts[index].duration;
			currentText.soundRef = DataAsset->texts[index].soundRef;
			currentText.line = DataAsset->texts[index].line;
			currentText.triggerType = DataAsset->texts[index].triggerType;
			index++;
			SubtitleEvent.Broadcast(ESubtitleEvent::SubtitleStarted);
		}
	}
}

void USubtitleComponent::Ended()
{
	index = 0;
	currentText.duration = DataAsset->texts[index].duration;
	currentText.soundRef = DataAsset->texts[index].soundRef;
	currentText.line = DataAsset->texts[index].line;
	currentText.triggerType = DataAsset->texts[index].triggerType;
	SubtitleEvent.Broadcast(ESubtitleEvent::SubtitleFinished);
}

FTextData USubtitleComponent::GetCurrentTextData()
{
	return currentText;
}

void USubtitleComponent::StartTimer(float duration)
{
	GetWorld()->GetTimerManager().SetTimer(ShowNextSubtitleTimerHandle, this, &USubtitleComponent::Next, 0, false, duration);
}

void USubtitleComponent::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ShowNextSubtitleTimerHandle);
}
