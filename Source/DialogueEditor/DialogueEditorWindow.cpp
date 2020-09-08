#include "DialogueEditor/DialogueEditorWindow.h"
#include "DialogueEditor/DialogueEditorWindowPanel.h"
#include "DialogueEditor/DialogueEditor.h"


void DialogueEditorWindow::OnStartupModule()
{
	FDialogueEditorWindowBase::OnStartupModule();
	FDialogueEditor::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &DialogueEditorWindow::MakeMenuEntry), FName("Section_1"));
}

void DialogueEditorWindow::OnShutdownModule()
{
	FDialogueEditorWindowBase::OnShutdownModule();
}

void DialogueEditorWindow::Initialize()
{
	TabName = "DialogueEditorWindow";
	TabDisplayName = FText::FromString("DialogueEditor Tool");
	ToolTipText = FText::FromString("Dialogue Editor Window");
}

TSharedRef<SDockTab> DialogueEditorWindow::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(DialogueEditorWindowPanel)
			.Tool(SharedThis(this))
		];

	return SpawnedTab;
}
