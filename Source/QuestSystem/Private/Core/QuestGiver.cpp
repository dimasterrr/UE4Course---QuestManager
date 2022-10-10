#include "Core/QuestGiver.h"

#include "Core/Quest.h"

class UWorldViewerSubsystem;

void AQuestGiver::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (const auto Actor : AttachedActors)
	{
		if (const auto Quest = Cast<AQuest>(Actor))
		{
			CachedQuests.Add(Quest->GetName(), Quest);
		}
	}
}

void AQuestGiver::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		if (Ar.IsSaving())
		{
			int32 QuestsCount = CachedQuests.Num();
			Ar << QuestsCount;

			for (auto Quest : CachedQuests)
			{
				Ar << Quest.Key;
				Quest.Value->Serialize(Ar);
			}
		}
		else
		{
			int32 QuestsCount;
			Ar << QuestsCount;

			FString Key;
			for (int32 i = 0; i < QuestsCount; ++i)
			{
				Ar << Key;
				for (auto Quest : CachedQuests)
				{
					if (Key == Quest.Key) Quest.Value->Serialize(Ar);
				}
			}
		}
	}
}
