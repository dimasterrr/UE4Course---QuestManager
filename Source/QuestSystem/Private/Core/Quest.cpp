#include "Core/Quest.h"

#include "Core/Objective.h"
#include "Objectives/CollectionObjective.h"
#include "Objectives/InteractionObjective.h"
#include "Objectives/LocationObjective.h"

void AQuest::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		Ar << IsTaken;
	}
	else
	{
		Ar << IsTaken;
	}
}

void AQuest::BeginPlay()
{
	Super::BeginPlay();
}

void AQuest::TakeQuest(AActor* TargetInstigator)
{
	if (IsTaken) return;

	for (auto i = 0; i < Objectives.Num(); i++)
	{
		auto* Objective = Objectives[i];
		if (!Objective) continue;

		Objective->ActivateObjective(TargetInstigator);
		Objective->CanBeCompleted = i == 0 || !ValidateOrder;
		Objective->OnObjectiveCompleted.AddUObject(this, &ThisClass::OnObjectiveCompleted);
	}

	IsTaken = true;
	OnQuestStatusChanged.Broadcast(this);
}

bool AQuest::IsCompleted() const
{
	if (ValidateOrder && Objectives.IsValidIndex(Objectives.Num() - 1))
	{
		return Objectives.Last()->IsCompleted;
	}

	for (const auto Item : Objectives)
	{
		if (!Item) continue;
		if (Item->IsCompleted) continue;

		return false;
	}

	return true;
}

void AQuest::OnObjectiveCompleted(UObjective* Objective)
{
	if (!ValidateOrder) return;

	int32 FindIndex = INDEX_NONE;
	const auto IsFind = Objectives.Find(Objective, FindIndex);
	if (!IsFind) return;

	const auto IsContainNextObjective = Objectives.IsValidIndex(FindIndex + 1);
	if (!IsContainNextObjective) return;

	Objectives[FindIndex + 1]->CanBeCompleted = true;
	OnQuestStatusChanged.Broadcast(this);
}

void AQuest::UpdateLocation()
{
	if (const auto ParentActor = GetAttachParentActor())
	{
		const auto ActorLocation = ParentActor->GetActorLocation();
		SetActorLocation(ActorLocation);
	}
}

void AQuest::AddInteractObjective()
{
	Objectives.Add(NewObject<UInteractionObjective>(this));
}

void AQuest::AddLocationObjective()
{
	Objectives.Add(NewObject<ULocationObjective>(this));
}

void AQuest::AddCollectionObjective()
{
	Objectives.Add(NewObject<UCollectionObjective>(this));
}
