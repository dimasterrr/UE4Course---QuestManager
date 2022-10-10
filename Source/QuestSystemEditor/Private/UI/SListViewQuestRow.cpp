#include "UI/SListViewQuestRow.h"

#include "ISinglePropertyView.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SListViewQuestRow::Construct(const FArguments& InArgs,
                                  const TSharedRef<STableViewBase>& InOwner,
                                  const AQuestListItem InItem)
{
	Item = InItem;

	SMultiColumnTableRow<AQuestListItem>::Construct(FSuperRowType::FArguments(), InOwner);
}

TSharedRef<SWidget> SListViewQuestRow::GenerateWidgetForColumn(const FName& ColumnName)
{
	if (!Item) return SNew(STextBlock).Text(FText::FromString("Quest Not Found"));

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	const FSinglePropertyParams SinglePropertyParams;

	if (ColumnName == "QuestName")
		return PropertyEditorModule.CreateSingleProperty(Item, "Name", SinglePropertyParams)
		                           .ToSharedRef();

	if (ColumnName == "QuestDescription")
		return PropertyEditorModule.CreateSingleProperty(Item, "Description", SinglePropertyParams)
		                           .ToSharedRef();

	if (ColumnName == "QuestType")
		return PropertyEditorModule.CreateSingleProperty(Item, "QuestType", SinglePropertyParams)
		                           .ToSharedRef();

	if (ColumnName == "QuestOrder")
		return PropertyEditorModule.CreateSingleProperty(Item, "ValidateOrder", SinglePropertyParams)
		                           .ToSharedRef();

	if (ColumnName == "QuestObjectives")
		return PropertyEditorModule.CreateSingleProperty(Item, "Objectives", SinglePropertyParams)
		                           .ToSharedRef();

	if (ColumnName == "QuestPrerequisite")
		return PropertyEditorModule.CreateSingleProperty(Item, "PrerequisiteQuest", SinglePropertyParams)
		                           .ToSharedRef();

	return SNew(STextBlock).Text(FText::FromString("Property Not Found"));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
