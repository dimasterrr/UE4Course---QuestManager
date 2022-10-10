#include "UI/QuestList.h"

#include "Components/QuestManagerComponent.h"
#include "Components/ScrollBox.h"
#include "UI/QuestDescription.h"
#include "UI/QuestListEntry.h"

void UQuestList::Setup(UQuestManagerComponent* QuestManagerComponent)
{
	if (!QuestManagerComponent || !QuestEntryClass) return;

	for (const auto Item : QuestManagerComponent->GetQuests())
	{
		const auto ScrollWidget = Item->QuestType == EQuestType::Story ? StoryQuestsList : SideQuestsList;
		if (!ScrollWidget) continue;

		const auto QuestEntry = CreateWidget<UQuestListEntry>(this, QuestEntryClass);
		QuestEntry->SetQuestText(Item->Name);
		QuestEntry->OnQuestChosen.BindUObject(QuestManagerComponent, &UQuestManagerComponent::SetActiveQuest, Item);

		QuestEntries.Add(Item, QuestEntry);
		ScrollWidget->AddChild(QuestEntry);
	}

	OnActiveQuestChanged(QuestManagerComponent->GetActiveQuest());
	QuestManagerComponent->OnActiveQuestChanged.AddDynamic(this, &UQuestList::OnActiveQuestChanged);
}

void UQuestList::OnActiveQuestChanged(AQuest* ActiveQuest)
{
	for (const auto Item : QuestEntries)
	{
		Item.Value->SetIsSelected(Item.Key == ActiveQuest);
	}

	if (ActiveQuestDescription)
	{
		ActiveQuestDescription->Setup(ActiveQuest);
		ActiveQuestDescription->SetVisibility(ActiveQuest ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
