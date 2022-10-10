#include "UI/QuestListEntry.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UQuestListEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (SelectQuestButton)
	{
		SelectQuestButton->OnReleased.AddDynamic(this, &ThisClass::UQuestListEntry::SelectQuest);
	}
}

void UQuestListEntry::SelectQuest()
{
	OnQuestChosen.ExecuteIfBound();
}

void UQuestListEntry::SetQuestText(const FText& Text)
{
	if (!QuestText) return;

	QuestText->SetText(Text);
}

void UQuestListEntry::SetIsSelected(const bool IsSelected)
{
	if (!SelectionBorder) return;

	SelectionBorder->SetBrushColor(IsSelected ? FLinearColor(1.f, 1.f, 1.f, 1.f) : FLinearColor(1.f, 1.f, 1.f, 0.f));
}
