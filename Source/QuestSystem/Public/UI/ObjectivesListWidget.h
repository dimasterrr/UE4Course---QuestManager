#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectivesListWidget.generated.h"

class UObjectiveWidget;
class AQuest;
class UVerticalBox;

UCLASS()
class QUESTSYSTEM_API UObjectivesListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

	UPROPERTY(meta = (BindWidgetOptional))
	UVerticalBox* ObjectivesList;

public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentObjectives(AQuest* Quest);	
};
