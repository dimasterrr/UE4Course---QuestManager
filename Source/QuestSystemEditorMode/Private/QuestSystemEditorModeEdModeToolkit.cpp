#include "QuestSystemEditorModeEdModeToolkit.h"
#include "QuestSystemEditorModeEdMode.h"
#include "Widgets/Input/SButton.h"
#include "EditorModeManager.h"
#include "AppFramework/Public/Widgets/Colors/SColorPicker.h"
#include "Core/Quest.h"
#include "Core/QuestGiver.h"
#include "Engine/Selection.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Objectives/CollectionObjective.h"
#include "Objectives/InteractionObjective.h"
#include "Objectives/LocationObjective.h"
#include "Widgets/Colors/SColorBlock.h"

#define LOCTEXT_NAMESPACE "FQuestSystemEditorModeEdModeToolkit"

FQuestSystemEditorModeEdModeToolkit::FQuestSystemEditorModeEdModeToolkit()
{
}

void FQuestSystemEditorModeEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	SAssignNew(ToolkitWidget, SBorder)
	.Padding(10.f)
	.VAlign(VAlign_Top)
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		[
			SNew(SButton)
				.Text(LOCTEXT("SelectNPCButtonLabel", "Select NPC"))
				.OnClicked(this, &FQuestSystemEditorModeEdModeToolkit::OnSelectNPCButtonClicked)
		]

		+ SVerticalBox::Slot()
		.Padding(FMargin(0.f, 10.f, 0.f, 0.f))
		[
			SNew(SColorBlock)
				.Color(this, &FQuestSystemEditorModeEdModeToolkit::GetNPCBoundingBoxColor)
				.OnMouseButtonDown(this, &FQuestSystemEditorModeEdModeToolkit::OnSelectNCPColorClicked)
		]

		+ SVerticalBox::Slot()
		[
			SNew(SColorBlock)
				.Color(this, &FQuestSystemEditorModeEdModeToolkit::GetObjectsBoundingBoxColor)
				.OnMouseButtonDown(this, &FQuestSystemEditorModeEdModeToolkit::OnSelectObjectColorClicked)
		]
	];

	FModeToolkit::Init(InitToolkitHost);
}

FName FQuestSystemEditorModeEdModeToolkit::GetToolkitFName() const
{
	return FName("QuestSystem Editor Mode");
}

FText FQuestSystemEditorModeEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("QuestSystemEditorModeEdModeToolkit", "DisplayName", "QuestSystem Editor Mode Tool");
}

class FEdMode* FQuestSystemEditorModeEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FQuestSystemEditorModeEdMode::EM_QuestSystemEditorModeEdModeId);
}

FLinearColor FQuestSystemEditorModeEdModeToolkit::GetNPCBoundingBoxColor() const
{
	const auto EditorMode = StaticCast<FQuestSystemEditorModeEdMode*>(GetEditorMode());
	return EditorMode->NPCBoundingBoxColor;
}

void FQuestSystemEditorModeEdModeToolkit::SetNPCBoundingBoxColor(const FLinearColor Value) const
{
	const auto EditorMode = StaticCast<FQuestSystemEditorModeEdMode*>(GetEditorMode());
	EditorMode->NPCBoundingBoxColor = Value;
}

FLinearColor FQuestSystemEditorModeEdModeToolkit::GetObjectsBoundingBoxColor() const
{
	const auto EditorMode = StaticCast<FQuestSystemEditorModeEdMode*>(GetEditorMode());
	return EditorMode->ObjectsBoundingBoxColor;
}

void FQuestSystemEditorModeEdModeToolkit::SetObjectsBoundingBoxColor(const FLinearColor Value) const
{
	const auto EditorMode = StaticCast<FQuestSystemEditorModeEdMode*>(GetEditorMode());
	EditorMode->ObjectsBoundingBoxColor = Value;
}

FReply FQuestSystemEditorModeEdModeToolkit::OnSelectNPCButtonClicked()
{
	const auto SelectedActors = GEditor->GetSelectedActors();
	bool OnlyNPC = true;
	
	TArray<AQuestGiver*> QuestGivers;
	for (FSelectionIterator Iterator(*SelectedActors); Iterator; ++Iterator)
	{
		if (auto Actor = Cast<AQuestGiver>(*Iterator))
		{
			QuestGivers.Add(Actor);
			OnlyNPC &= true;
			continue;
		}

		OnlyNPC &= false;
	}

	// Unselect all
	GEditor->SelectNone(true, true);

	if (OnlyNPC)
	{
		// Select objectives
		for (const auto QuestGiver : QuestGivers)
		{
			TArray<AActor*> AttachedActors;
			QuestGiver->GetAttachedActors(AttachedActors);

			TArray<AActor*> ActorQuests = AttachedActors.FilterByPredicate([](AActor* Item)
			{
				return Item->GetClass() == AQuest::StaticClass()
					|| Cast<AQuest>(Item);
			});

			TArray<UObjective*> QuestObjectives;
			for (const auto ActorQuest : ActorQuests)
			{
				const auto Quest = Cast<AQuest>(ActorQuest);
				QuestObjectives.Append(Quest->Objectives);
			}

			TArray<AActor*> TargetObjectives;
			for (const auto QuestObjective : QuestObjectives)
			{
				if (const auto InteractionObjective = Cast<UInteractionObjective>(QuestObjective))
				{
					TargetObjectives.Add(InteractionObjective->Target);
				}
				else if (const auto LocationObjective = Cast<ULocationObjective>(QuestObjective))
				{
					TargetObjectives.Add(LocationObjective->Target);
				}
				else if (const auto CollectionObjective = Cast<UCollectionObjective>(QuestObjective))
				{
					TArray<AActor*> ObjectiveActors;
					UGameplayStatics::GetAllActorsOfClass(GEditor->EditorWorld,
					                                      CollectionObjective->CollectableActorClass,
					                                      ObjectiveActors);
					TargetObjectives.Append(ObjectiveActors);
				}
			}

			for (const auto Item : TargetObjectives)
			{
				GEditor->SelectActor(Item, true, true);
			}
		}
	}
	else
	{
		// Select quest givers
		for (auto* QuestNPC : QuestGivers)
		{
			GEditor->SelectActor(QuestNPC, true, true);
		}
	}

	return FReply::Handled();
}

FReply FQuestSystemEditorModeEdModeToolkit::OnSelectNCPColorClicked(const FGeometry& MyGeometry,
                                                                    const FPointerEvent& MouseEvent)
{
	FColorPickerArgs PickerArgs;
	PickerArgs.InitialColorOverride = GetNPCBoundingBoxColor();
	PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(
		this, &FQuestSystemEditorModeEdModeToolkit::SetNPCBoundingBoxColor);

	OpenColorPicker(PickerArgs);

	return FReply::Handled();
}

FReply FQuestSystemEditorModeEdModeToolkit::OnSelectObjectColorClicked(const FGeometry& MyGeometry,
                                                                       const FPointerEvent& MouseEvent)
{
	FColorPickerArgs PickerArgs;
	PickerArgs.InitialColorOverride = GetObjectsBoundingBoxColor();
	PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(
		this, &FQuestSystemEditorModeEdModeToolkit::SetObjectsBoundingBoxColor);

	OpenColorPicker(PickerArgs);
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
