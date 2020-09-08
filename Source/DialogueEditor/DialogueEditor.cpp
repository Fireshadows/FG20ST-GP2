#include "DialogueEditor.h"
#include "IDialogueModuleInterface.h"
#include "MenuTool/MenuTool.h"
#include "DialogueEditorWindow.h"
IMPLEMENT_GAME_MODULE(FDialogueEditor, DialogueEditor)

TSharedRef<FWorkspaceItem> FDialogueEditor::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

void FDialogueEditor::AddModuleListeners()
{
    // add tools later

	ModuleListeners.Add(MakeShareable(new MenuTool));

	ModuleListeners.Add(MakeShareable(new DialogueEditorWindow));
}

void FDialogueEditor::AddMenuExtension(const FMenuExtensionDelegate& extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList>& CommandList /*= NULL*/, EExtensionHook::Position position /*= EExtensionHook::Before*/)
{
    MenuExtender->AddMenuExtension(extensionHook, position, CommandList, extensionDelegate);
}

void FDialogueEditor::MakePulldownMenu(FMenuBarBuilder& menuBuilder)
{
	menuBuilder.AddPullDownMenu(
		FText::FromString("DialogueEditor"),
		FText::FromString("Open the DialogueEditor menu"),
		FNewMenuDelegate::CreateRaw(this, &FDialogueEditor::FillPulldownMenu),
		"DialogueEditor",
		FName(TEXT("DialogueEditor"))
	);
}

void FDialogueEditor::FillPulldownMenu(FMenuBuilder& menuBuilder)
{
	// just a frame for tools to fill in
	menuBuilder.BeginSection("Open", FText::FromString("Open"));
	menuBuilder.AddMenuSeparator(FName("Section_1"));
	menuBuilder.EndSection();
}

void FDialogueEditor::StartupModule()
{
	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension("Window", EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FDialogueEditor::MakePulldownMenu));
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);
	}
    IDialogueModuleInterface::StartupModule();
}

void FDialogueEditor::ShutdownModule()
{
    IDialogueModuleInterface::ShutdownModule();
}