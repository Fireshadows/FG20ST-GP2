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
		switch (DataAsset->texts[index].triggerType)
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
	index++;
	if (index < DataAsset->texts.Num())
	{
		SubtitleEvent.Broadcast(ESubtitleEvent::SubtitleNext);
	}
	else
	{
		Ended();
	}
}	
void USubtitleComponent::Start()
{
	SubtitleEvent.Broadcast(ESubtitleEvent::SubtitleStarted);
}

void USubtitleComponent::Ended()
{
	index = 0;
	SubtitleEvent.Broadcast(ESubtitleEvent::SubtitleFinished);
}

FTextData USubtitleComponent::GetCurrentTextData()
{
	if (index >= 0)
	{
		return DataAsset->texts[index];
	}
	return FTextData();
}

void USubtitleComponent::StartTimer(float duration)
{
	GetWorld()->GetTimerManager().SetTimer(ShowNextSubtitleTimerHandle, this, &USubtitleComponent::Next, 0, false, duration);
}

void USubtitleComponent::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ShowNextSubtitleTimerHandle);
}
