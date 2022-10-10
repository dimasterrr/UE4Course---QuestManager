#include "UI/QuestDialog.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/QuestDescription.h"

void UQuestDialog::NativeConstruct()
{
	Super::NativeConstruct();

	if (AcceptButton)
	{
		AcceptButton->OnReleased.AddDynamic(this, &UQuestDialog::OnAccepted);
	}

	if (RejectButton)
	{
		RejectButton->OnReleased.AddDynamic(this, &UQuestDialog::OnRejected);
	}

	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC, this);
	PC->SetShowMouseCursor(true);
}

void UQuestDialog::OnAccepted()
{
	HideDialog();
	
	if (!OnQuestAccepted.IsBound()) return;
	OnQuestAccepted.Broadcast();
}

void UQuestDialog::OnRejected()
{
	HideDialog();

	if (!OnDialogExit.IsBound()) return;
	OnDialogExit.Broadcast();
}

void UQuestDialog::HideDialog()
{
	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	PC->SetShowMouseCursor(false);

	RemoveFromViewport();
}

void UQuestDialog::Setup(AQuest* Quest)
{
	if (Description)
	{
		Description->Setup(Quest);
	}
}
