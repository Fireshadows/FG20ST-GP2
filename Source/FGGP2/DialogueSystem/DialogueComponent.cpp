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

int UDialogueComponent::AddBranch(int key)
{
	FDialogueData branchNode;
	branchNode.bIsBranch = true;
	lines.Add(branchNode);
	if (lines.Num() > key)
	{
		FNodeData nodeData;
		nodeData.index = lines.Num() - 1;
		nodeData.keyWord = -1;
		lines[key].children.Add(nodeData);
	}
	return lines.Num() - 1;
}

int UDialogueComponent::AddLineToBranch(int key, FBranchInput dialogueInput, float timer)
{
	if (lines.Num() > key)
	{
		FDialogueData branchData;
		branchData.line = dialogueInput.line;
		branchData.timer = timer;
		lines.Add(branchData);
		FNodeData nodeData;
		nodeData.index = lines.Num() - 1;
		nodeData.keyWord = dialogueInput.keyWord;
		lines[key].children.Add(nodeData);
		return lines.Num() - 1;
	}
	return -1; //TODO: warning
}

bool UDialogueComponent::HasChild() const
{
	return lines[currentIndex].children[0].index > 0 && lines[currentIndex].children[0].index < lines.Num();
}

void UDialogueComponent::AddReturnNode(int key, int returnTo)
{
	FNodeData nodeData;
	nodeData.index = returnTo;
	nodeData.keyWord = -1;
	lines[key].children.Add(nodeData);
}

void UDialogueComponent::Start()
{
	if (lines.Num() > 0)
	{
		bStarted = true;
		currentIndex = 0;
		DialogueStarted.Broadcast();
	}
}

void UDialogueComponent::Next()
{
	if (bStarted)
	{
		if (lines[currentIndex].children.Num() == 0)
		{
			Stop();
			return;
		}
		if (!AtBranch())
		{
			currentIndex = lines[currentIndex].children[0].index;
			DialogueNext.Broadcast();
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
		return lines[currentIndex].bIsBranch;
	}
	return false;
}

bool UDialogueComponent::EnterKeyword(int keyword)
{
	for (int i = 0; i < lines.Num(); i++)
	{
		for (int j = 0; j < lines[i].children.Num(); j++)
		{
			if (lines[i].children[j].keyWord == keyword)
			{
				currentIndex = lines[i].children[j].index;
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

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
}
