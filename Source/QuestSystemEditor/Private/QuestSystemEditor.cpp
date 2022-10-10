#include "QuestSystemEditor.h"
#include "QuestSystemEditorStyle.h"
#include "QuestSystemEditorCommands.h"
#include "LevelEditor.h"
#include "ToolMenus.h"

#include "Widgets/Docking/SDockTab.h"
#include "UI/SQuestsEditor.h"

static const FName QuestSystemEditorTabName("QuestSystemEditor");

#define LOCTEXT_NAMESPACE "FQuestSystemEditorModule"

void FQuestSystemEditorModule::StartupModule()
{
	FQuestSystemEditorStyle::Initialize();
	FQuestSystemEditorStyle::ReloadTextures();

	FQuestSystemEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuestSystemEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FQuestSystemEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FQuestSystemEditorModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(QuestSystemEditorTabName,
	                                                  FOnSpawnTab::CreateRaw(
		                                                  this, &FQuestSystemEditorModule::OnSpawnPluginTab))
	                        .SetDisplayName(LOCTEXT("FQuestSystemEditorTabTitle", "Quest System Editor"))
	                        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FQuestSystemEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FQuestSystemEditorStyle::Shutdown();
	FQuestSystemEditorCommands::Unregister();
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(QuestSystemEditorTabName);
}

TSharedRef<SDockTab> FQuestSystemEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SQuestsEditor)
		];
}

void FQuestSystemEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(QuestSystemEditorTabName);
}

void FQuestSystemEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FQuestSystemEditorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(FQuestSystemEditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FQuestSystemEditorModule, QuestSystemEditor)
