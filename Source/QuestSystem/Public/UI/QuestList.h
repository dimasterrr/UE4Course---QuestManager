#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestList.generated.h"

class UQuestListEntry;
class UQuestDescription;
class AQuest;
class UScrollBox;
class UQuestManagerComponent;

UCLASS()
class QUESTSYSTEM_API UQuestList : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox* StoryQuestsList;

	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox* SideQuestsList;

	UPROPERTY(meta = (BindWidgetOptional))
	UQuestDescription* ActiveQuestDescription;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestListEntry> QuestEntryClass;

	UPROPERTY()
	TMap<AQuest*, UQuestListEntry*> QuestEntries;

protected:
	void OnActiveQuestChanged(AQuest* ActiveQuest);

public:
	UFUNCTION(BlueprintCallable)
	void Setup(UQuestManagerComponent* QuestManagerComponent);
};
