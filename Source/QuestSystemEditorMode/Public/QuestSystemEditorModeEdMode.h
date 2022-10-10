#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

class FQuestSystemEditorModeEdMode : public FEdMode
{
protected:
	TArray<AActor*> SelectedActors;
	
public:
	const static FEditorModeID EM_QuestSystemEditorModeEdModeId;

	FLinearColor NPCBoundingBoxColor = FLinearColor::Blue;
	FLinearColor ObjectsBoundingBoxColor = FLinearColor::Red;

protected:
	void UpdateSelectedActors();
	
public:
	FQuestSystemEditorModeEdMode();
	virtual ~FQuestSystemEditorModeEdMode();

	virtual void Enter() override;
	virtual void Exit() override;
	bool UsesToolkits() const override;

	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View,
	                     FCanvas* Canvas) override;
	virtual void ActorSelectionChangeNotify() override;
};
