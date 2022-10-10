#include "UI/ObjectiveWidget.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Core/Objective.h"

void UObjectiveWidget::Setup(const UObjective* Objective) const
{
	if (!Objective) return;

	if (StatusCheckBox)
	{
		StatusCheckBox->SetIsChecked(Objective->IsCompleted);
	}

	if (DescriptionText)
	{
		DescriptionText->SetText(Objective->Description);
	}
}
