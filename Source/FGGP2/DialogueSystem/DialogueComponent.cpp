#include "DialogueComponent.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	currentIndex = -1;
	bStarted = false;
}

int UDialogueComponent::InitializeText(FText dialogueInput, float timer)
{
	FDialogueData data;
	data.line = dialogueInput;
	data.timer = timer;
	lines.Add(data);
	return 0;
}

int UDialogueComponent::AddLine(int key, FText dialogueInput, float timer)
{
	FDialogueData data;
	data.line = dialogueInput;
	data.timer = timer;
	lines.Add(data);
	if (lines.Num() > key)
	{
		FNodeData nodeData;
		nodeData.index = lines.Num()-1;
		nodeData.keyWord = -1;
		lines[key].children.Add(nodeData);
	}
	return lines.Num()-1;
}

int UDialogueComponent::AddBranch(int key, FBranchInput dialogueInput, float timer)
{
	FDialogueData data;
	data.line = dialogueInput.line;
	data.timer = timer;
	lines.Add(data);
	if (lines.Num() > key)
	{
		FNodeData nodeData;
		nodeData.index = lines.Num()-1;
		nodeData.keyWord = dialogueInput.keyWord;
		lines[key].children.Add(nodeData);
		return lines.Num()-1;
	}
	return -1;
}

void UDialogueComponent::Start()
{
	if (lines.Num() > 0)
	{
		bStarted = true;
		currentIndex = 0;
		TestIfWaitingForKeyword();
		DialogueStarted.Broadcast();
	}

}

void UDialogueComponent::Next()
{
	if (bStarted)
	{
		if (lines[currentIndex].children.Num() == 0
		{
			Stop();
			return;
		}
		if (!bWaitingForKeyword)
		{
			if (lines[currentIndex].children[0].index > 0 && lines[currentIndex].children[0].index < lines.Num())
			{
				currentIndex = lines[currentIndex].children[0].index;
				TestIfWaitingForKeyword();
				DialogueNext.Broadcast();
			}
			else
			{
				//TODO: Warning
			}
		}
	}
}

void UDialogueComponent::Stop()
{
	currentIndex = -1;
	bStarted = false;
	DialogueStopped.Broadcast();
}

bool UDialogueComponent::AtBranch() const
{
	if (currentIndex > 0 && currentIndex < lines.Num())
	{
		return lines[currentIndex].children.Num() > 1;
	}
	return false;
}

bool UDialogueComponent::EnterKeyword(int keyword)
{
	if (bWaitingForKeyword)
	{
		for (int i = 0; i < lines[currentIndex].children.Num(); i++)
		{
			if (lines[currentIndex].children[i].keyWord == keyword)
			{
				currentIndex = lines[currentIndex].children[i].index;
				TestIfWaitingForKeyword();
				DialogueNext.Broadcast();
				return true;
			}
		}
	}
	return false;
}

FDialogueData UDialogueComponent::GetCurrentText() const
{
	if (currentIndex != -1 && currentIndex < lines.Num())
	{
		return lines[currentIndex];
	}
	return FDialogueData();
}

void UDialogueComponent::TestIfWaitingForKeyword()
{
	if (lines[currentIndex].children.Num() > 1 || lines[currentIndex].children.Num() == 1)
	{
		for (int i = 0; i < lines[currentIndex].children.Num(); i++)
		{
			if (lines[currentIndex].children[i].keyWord != -1)
			{
				bWaitingForKeyword = true;
				DialogueAtBranch.Broadcast();
				return;
			}
		}
	}
	bWaitingForKeyword = false;
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
}
