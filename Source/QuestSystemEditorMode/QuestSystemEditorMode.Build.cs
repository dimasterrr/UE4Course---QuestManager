using UnrealBuildTool;

public class QuestSystemEditorMode : ModuleRules
{
	public QuestSystemEditorMode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AppFramework",
				"CoreUObject",
				"Engine",
				"InputCore",
				"LevelEditor",
				"QuestSystem",
				"Slate",
				"SlateCore",
				"UnrealEd",
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}