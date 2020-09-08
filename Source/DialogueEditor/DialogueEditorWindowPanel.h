#pragma once
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Docking/SDockableTab.h"
#include "Widgets/Docking/SDockTabStack.h"
#include "Framework/Application/SlateApplication.h"
#include "DialogueEditor/DialogueEditorWindow.h"

class DialogueEditorWindowPanel : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(DialogueEditorWindowPanel)
	{}
	SLATE_ARGUMENT(TWeakPtr<class DialogueEditorWindow>, Tool)
		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs);

protected:
	TWeakPtr<DialogueEditorWindow> tool;
};