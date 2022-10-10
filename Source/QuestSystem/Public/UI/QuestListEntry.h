#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestListEntry.generated.h"

class UBorder;
class UButton;
class UTextBlock;

UCLASS()
class QUESTSYSTEM_API UQuestListEntry : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* QuestText;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* SelectQuestButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UBorder* SelectionBorder;

public:
	FSimpleDelegate OnQuestChosen;

protected:
	UFUNCTION()
	void SelectQuest();

public:
	virtual void NativeConstruct() override;

	void SetQuestText(const FText& Text);
	void SetIsSelected(bool IsSelected);
};
