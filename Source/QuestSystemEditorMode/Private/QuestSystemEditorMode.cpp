#include "QuestSystemEditorMode.h"
#include "QuestSystemEditorModeEdMode.h"

#define LOCTEXT_NAMESPACE "FQuestSystemEditorModeModule"

void FQuestSystemEditorModeModule::StartupModule()
{
	FEditorModeRegistry::Get().RegisterMode<FQuestSystemEditorModeEdMode>(
		FQuestSystemEditorModeEdMode::EM_QuestSystemEditorModeEdModeId,
		LOCTEXT("QuestSystemEditorModeEdModeName", "QuestSystem Editor Mode"),
		FSlateIcon(),
		true);
}

void FQuestSystemEditorModeModule::ShutdownModule()
{
	FEditorModeRegistry::Get().UnregisterMode(FQuestSystemEditorModeEdMode::EM_QuestSystemEditorModeEdModeId);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FQuestSystemEditorModeModule, QuestSystemEditorMode)
