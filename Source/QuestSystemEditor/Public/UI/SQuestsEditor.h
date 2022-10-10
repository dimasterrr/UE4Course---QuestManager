#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Core/Quest.h"

using AQuestListItem = AQuest*;
using FQuestListArray = TArray<AQuestListItem>;
using SQuestListView = SListView<AQuestListItem>;
using FQuestViewShared = TSharedPtr<SQuestListView>;

class QUESTSYSTEMEDITOR_API SQuestsEditor final : public SCompoundWidget
{
private:
	FQuestListArray QuestListItems;
	FQuestViewShared QuestListView;

public:
	SLATE_BEGIN_ARGS(SQuestsEditor)
		{
		}

	SLATE_END_ARGS()

private:
	void OnModulesChanged(FName Name, EModuleChangeReason ModuleChangeReason);

	TSharedRef<ITableRow> OnQuestItemGenerated(const AQuestListItem Item,
	                                           const TSharedRef<STableViewBase>& OwnerTable);
	TSharedRef<SHeaderRow> GenerateListHeader() const;

	FReply OnShowSelectedQuestsButtonClicked();

public:
	SQuestsEditor();
	~SQuestsEditor();
	
	void Construct(const FArguments& InArgs);
};
