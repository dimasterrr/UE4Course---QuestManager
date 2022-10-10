#include "Components/QuestManagerComponent.h"

void UQuestManagerComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		if (Ar.IsSaving())
		{
			int32 QuestsCount = AcceptedQuests.Num();
			Ar << QuestsCount;

			for (const auto Quest : AcceptedQuests) Quest->Serialize(Ar);

			bool HasActiveQuest = !!ActiveQuest;
			Ar << HasActiveQuest;

			if (HasActiveQuest) ActiveQuest->Serialize(Ar);
		}
		else
		{
			AcceptedQuests.Reset();

			int32 QuestsCount;
			Ar << QuestsCount;

			for (int32 i = 0; i < QuestsCount; ++i)
			{
				AQuest* Quest = nullptr;
				Quest->Serialize(Ar);
				AcceptedQuests.AddUnique(Quest);
			}

			bool HasActiveQuest;
			Ar << HasActiveQuest;

			if (HasActiveQuest) ActiveQuest->Serialize(Ar);
			OnActiveQuestChanged.Broadcast(ActiveQuest);
		}
	}
}

void UQuestManagerComponent::AddQuest(AQuest* Quest)
{
	if (!Quest) return;

	if (!ActiveQuest || ActiveQuest->IsCompleted())
	{
		ActiveQuest = Quest;
		OnActiveQuestChanged.Broadcast(ActiveQuest);
	}

	AcceptedQuests.AddUnique(Quest);
	Quest->TakeQuest(GetOwner());
	Quest->OnQuestStatusChanged.AddLambda([this](AQuest* TargetQuest)
	{
		if (ActiveQuest != TargetQuest) return;
		OnActiveQuestChanged.Broadcast(TargetQuest);
	});
}

const TArray<AQuest*>& UQuestManagerComponent::GetQuests()
{
	return AcceptedQuests;
}

AQuest* UQuestManagerComponent::GetActiveQuest() const
{
	return ActiveQuest;
}

void UQuestManagerComponent::SetActiveQuest(AQuest* Quest)
{
	if (!AcceptedQuests.Contains(Quest)) return;

	ActiveQuest = Quest;
	OnActiveQuestChanged.Broadcast(ActiveQuest);
}
