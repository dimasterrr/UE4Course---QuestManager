#pragma once

#include "CoreMinimal.h"
#include "SQuestsEditor.h"

class QUESTSYSTEMEDITOR_API SListViewQuestRow : public SMultiColumnTableRow<AQuestListItem>
{
private:
	AQuestListItem Item;

public:
	SLATE_BEGIN_ARGS(SListViewQuestRow)
		{
		}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner, const AQuestListItem InItem);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;
};
