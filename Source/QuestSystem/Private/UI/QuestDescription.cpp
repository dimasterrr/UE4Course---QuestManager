#include "UI/QuestDescription.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Core/Quest.h"
#include "UI/ObjectiveWidget.h"

void UQuestDescription::Setup(AQuest* Quest)
{
	if (!Quest) return;

	NameText->SetText(Quest->Name);
	DescriptionText->SetText(Quest->Description);

	if (!ObjectiveWidgetClass) return;

	ObjectivesList->ClearChildren();
	for (const auto Objective : Quest->Objectives)
	{
		const auto ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
		ObjectiveWidget->Setup(Objective);

		ObjectivesList->AddChild(ObjectiveWidget);
	}
}
