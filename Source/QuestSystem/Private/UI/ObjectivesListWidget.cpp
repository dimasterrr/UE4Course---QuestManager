#include "UI/ObjectivesListWidget.h"

#include "Components/VerticalBox.h"
#include "Core/Quest.h"
#include "UI/ObjectiveWidget.h"

void UObjectivesListWidget::SetCurrentObjectives(AQuest* Quest)
{
	if (!ObjectivesList || !ObjectiveWidgetClass) return;
	ObjectivesList->ClearChildren();

	if (!Quest) return;

	for (const auto Item : Quest->Objectives)
	{
		const auto NewObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
		NewObjectiveWidget->Setup(Item);

		ObjectivesList->AddChildToVerticalBox(NewObjectiveWidget);
	}
}
