#include "UI/SQuestsEditor.h"

#include "EngineUtils.h"
#include "SlateOptMacros.h"
#include "Engine/Selection.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SListViewQuestRow.h"
#include "Widgets/Layout/SSeparator.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SQuestsEditor::SQuestsEditor()
{
	// FModuleManager::Get().OnModulesChanged().AddSP(this, &SQuestsEditor::OnModulesChanged);
}

SQuestsEditor::~SQuestsEditor()
{
	// FModuleManager::Get().OnModulesChanged().RemoveAll(this);
}

void SQuestsEditor::OnModulesChanged(FName Name, EModuleChangeReason ModuleChangeReason)
{
}

void SQuestsEditor::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)

		// Toolbar
		+ SVerticalBox::Slot()
		  .MaxHeight(24.f)
		  .HAlign(HAlign_Left)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
					.Text(NSLOCTEXT("QuestSystemEditor", "ShowSelectedQuestsButton", "Show selected quests from world"))
					.OnClicked(this, &SQuestsEditor::OnShowSelectedQuestsButtonClicked)
			]
		]

		// Content
		+ SVerticalBox::Slot()
		  .FillHeight(1.f)
		  .Padding(FMargin(0.f, 10.f, 0.f, 0.f))
		[
			SAssignNew(QuestListView, SQuestListView)
				.ItemHeight(24)
				.ListItemsSource(&QuestListItems)
				.HeaderRow(GenerateListHeader())
				.OnGenerateRow(this, &SQuestsEditor::OnQuestItemGenerated)
		]
	];
}

TSharedRef<SHeaderRow> SQuestsEditor::GenerateListHeader() const
{
	return
		SNew(SHeaderRow)

		+ SHeaderRow::Column("QuestName")
		.DefaultLabel(NSLOCTEXT("QuestSystemEditor", "QuestName", "Name"))

		+ SHeaderRow::Column("QuestDescription")
		.DefaultLabel(NSLOCTEXT("QuestSystemEditor", "QuestDescription", "Description"))

		+ SHeaderRow::Column("QuestType")
		.DefaultLabel(NSLOCTEXT("QuestSystemEditor", "QuestType", "Type"))

		+ SHeaderRow::Column("QuestOrder")
		.DefaultLabel(NSLOCTEXT("QuestSystemEditor", "QuestOrder", "Order"))

		+ SHeaderRow::Column("QuestObjectives")
		.DefaultLabel(NSLOCTEXT("QuestSystemEditor", "QuestObjectives", "Objectives"))

		+ SHeaderRow::Column("QuestPrerequisite")
		.DefaultLabel(NSLOCTEXT("QuestSystemEditor", "QuestPrerequisite", "Prerequisite Quest"));
}

TSharedRef<ITableRow> SQuestsEditor::OnQuestItemGenerated(const AQuestListItem Item,
                                                          const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SListViewQuestRow, OwnerTable, Item);
}

FReply SQuestsEditor::OnShowSelectedQuestsButtonClicked()
{
	if (!GEditor) return FReply::Unhandled();

	QuestListItems.Reset();
	for (auto Iterator = GEditor->GetSelectedActorIterator(); Iterator; ++Iterator)
	{
		if (const auto Quest = Cast<AQuest>(*Iterator))
			QuestListItems.Add(Quest);
	}

	GEditor->SelectNone(true, true);

	QuestListView->RequestListRefresh();
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
