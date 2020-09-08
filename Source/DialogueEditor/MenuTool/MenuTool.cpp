#include "MenuTool.h"
#include "DialogueEditor/DialogueEditor.h"


#define LOCTEXT_NAMESPACE "MenuTool"

class MenuToolCommands : public TCommands<MenuToolCommands>
{
public:
    MenuToolCommands()
        : TCommands<MenuToolCommands>(
              TEXT("MenuTool"),                       // Context name for fast lookup
              FText::FromString("Example Menu tool"), // Context name for displaying
              NAME_None,                              // No parent context
              FEditorStyle::GetStyleSetName()         // Icon Style Set
          )
    {
    }

    virtual void RegisterCommands() override
    {
        UI_COMMAND(MenuCommand1, "Menu Command 1", "Test Menu Command 1.", EUserInterfaceActionType::Button, FInputGesture());
    }

public:
    TSharedPtr<FUICommandInfo> MenuCommand1;
};

void MenuTool::MapCommands()
{
    const auto &Commands = MenuToolCommands::Get();

    CommandList->MapAction(
        Commands.MenuCommand1,
        FExecuteAction::CreateSP(this, &MenuTool::MenuCommand1),
        FCanExecuteAction());
}

void MenuTool::MakeMenuEntry(FMenuBuilder &menuBuilder)
{
    menuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand1);
}

void MenuTool::OnStartupModule()
{
	CommandList = MakeShareable(new FUICommandList);
	MenuToolCommands::Register();
    MapCommands();
	FDialogueEditor::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(this, &MenuTool::MakeMenuEntry),
		FName("Section_1"),
		CommandList);
}

void MenuTool::OnShutdownModule()
{
    MenuToolCommands::Unregister();
}

void MenuTool::MenuCommand1()
{
    UE_LOG(LogTemp, Warning, TEXT("clicked MenuCommand1"));
}

#undef LOCTEXT_NAMESPACE
