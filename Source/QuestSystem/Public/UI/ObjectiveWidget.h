#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

class UObjective;
class UTextBlock;
class UCheckBox;

UCLASS()
class QUESTSYSTEM_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UCheckBox* StatusCheckBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;

public:
	void Setup(const UObjective* Objective) const;
};
