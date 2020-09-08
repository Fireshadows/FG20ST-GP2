#pragma once
#include "DialogueEditor/DialogueEditorWindowBase.h"

class DialogueEditorWindow : public FDialogueEditorWindowBase
{
public:
	virtual ~DialogueEditorWindow() {}
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;
	virtual void Initialize() override;
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs) override;

};