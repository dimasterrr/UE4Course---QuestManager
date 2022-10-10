#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestDialog.generated.h"

class UQuestDescription;
class AQuest;
class UButton;

UCLASS()
class QUESTSYSTEM_API UQuestDialog : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestAccepted);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogExit);

protected:
	UPROPERTY(meta = (BindWidget))
	UQuestDescription* Description;

	UPROPERTY(meta = (BindWidget))
	UButton* AcceptButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RejectButton;

public:
	UPROPERTY(BlueprintAssignable)
	FOnQuestAccepted OnQuestAccepted;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogExit OnDialogExit;

protected:
	UFUNCTION(BlueprintCallable)
	void OnAccepted();

	UFUNCTION(BlueprintCallable)
	void OnRejected();
	
	UFUNCTION(BlueprintCallable)
	void HideDialog();

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Setup(AQuest* Quest);
};
