#pragma once
#include "DialogueEditor/IDialogueModuleInterface.h"

class MenuTool : public IDialogueModuleListenerInterface, public TSharedFromThis<MenuTool>
{
public:
    virtual ~MenuTool() {}
    void MakeMenuEntry(FMenuBuilder &menuBuilder);
    void OnStartupModule() override;
    void OnShutdownModule() override;

protected:
    TSharedPtr<FUICommandList> CommandList;
    void MapCommands();
    void MenuCommand1();
};