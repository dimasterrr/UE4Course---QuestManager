#include "QuestSystemEditorModeEdMode.h"
#include "QuestSystemEditorModeEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "Core/Objective.h"
#include "Core/QuestGiver.h"
#include "Engine/Selection.h"

const FEditorModeID FQuestSystemEditorModeEdMode::EM_QuestSystemEditorModeEdModeId = TEXT(
	"EM_QuestSystemEditorModeEdMode");

FQuestSystemEditorModeEdMode::FQuestSystemEditorModeEdMode()
{
}

FQuestSystemEditorModeEdMode::~FQuestSystemEditorModeEdMode()
{
}

void FQuestSystemEditorModeEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FQuestSystemEditorModeEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}

	UpdateSelectedActors();
}

void FQuestSystemEditorModeEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	FEdMode::Exit();
}

bool FQuestSystemEditorModeEdMode::UsesToolkits() const
{
	return true;
}

void FQuestSystemEditorModeEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);

	for (const auto Item : SelectedActors)
	{
		const auto IsNPC = !!Cast<AQuestGiver>(Item);

		DrawWireBox(PDI,
		            Item->GetComponentsBoundingBox(true),
		            IsNPC ? NPCBoundingBoxColor : ObjectsBoundingBoxColor,
		            1);
	}
}

void FQuestSystemEditorModeEdMode::DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport,
                                           const FSceneView* View, FCanvas* Canvas)
{
	FEdMode::DrawHUD(ViewportClient, Viewport, View, Canvas);

	for (const AActor* Item : SelectedActors)
	{
		if (Canvas)
		{
			FBox Bounds = Item->GetComponentsBoundingBox(true);

			FVector DrawPos = Bounds.GetCenter() + FVector(0.f, 0.f, Bounds.GetExtent().Z);
			FVector2D PixelLocation;
			View->ScreenToPixel(View->WorldToScreen(DrawPos), PixelLocation);
			PixelLocation /= ViewportClient->GetDPIScale();

			const auto RenderFont = GEngine->GetSmallFont();
			Canvas->DrawShadowedText(PixelLocation.X, PixelLocation.Y, FText::FromString(Item->GetName()), RenderFont,
			                         FLinearColor::Black);
		}
	}
}

void FQuestSystemEditorModeEdMode::ActorSelectionChangeNotify()
{
	FEdMode::ActorSelectionChangeNotify();

	UpdateSelectedActors();
}

void FQuestSystemEditorModeEdMode::UpdateSelectedActors()
{
	SelectedActors.Empty();

	if (!GEditor) return;

	USelection* ActorsSelection = GEditor->GetSelectedActors();
	for (FSelectionIterator Iterator(*ActorsSelection); Iterator; ++Iterator)
	{
		AActor* LevelActor = Cast<AActor>(*Iterator);
		if (LevelActor && !SelectedActors.Contains(LevelActor))
		{
			SelectedActors.Add(LevelActor);
		}
	}
}
