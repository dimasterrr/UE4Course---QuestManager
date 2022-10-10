#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"

class FQuestSystemEditorModeEdModeToolkit : public FModeToolkit
{
private:
	TSharedPtr<SWidget> ToolkitWidget;

private:
	FReply OnSelectNPCButtonClicked();
	FReply OnSelectNCPColorClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
	FReply OnSelectObjectColorClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	FLinearColor GetNPCBoundingBoxColor() const;
	void SetNPCBoundingBoxColor(FLinearColor Value) const;
	
	FLinearColor GetObjectsBoundingBoxColor() const;
	void SetObjectsBoundingBoxColor(FLinearColor Value) const;
	
public:
	FQuestSystemEditorModeEdModeToolkit();
	
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }

	
};
