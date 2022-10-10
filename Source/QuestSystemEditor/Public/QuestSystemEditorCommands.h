#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "QuestSystemEditorStyle.h"

class FQuestSystemEditorCommands : public TCommands<FQuestSystemEditorCommands>
{
public:
	FQuestSystemEditorCommands()
		: TCommands<FQuestSystemEditorCommands>(TEXT("QuestSystemEditor"),
		                                        NSLOCTEXT("Contexts", "QuestSystemEditor", "QuestSystemEditor Plugin"),
		                                        NAME_None,
		                                        FQuestSystemEditorStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenPluginWindow;
};
