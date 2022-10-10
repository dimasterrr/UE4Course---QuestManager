#include "Objectives/CollectionObjective.h"

#include "Core/CollectableInterface.h"
#include "Kismet/GameplayStatics.h"

UCollectionObjective::UCollectionObjective()
{
	Type = EObjectiveType::Collect;
}

void UCollectionObjective::ActivateObjective(AActor* TargetInstigator)
{
	Super::ActivateObjective(TargetInstigator);

	TArray<AActor*> ActorsToCollect;
	UGameplayStatics::GetAllActorsOfClass(this, CollectableActorClass, ActorsToCollect);

	for (const auto Item : ActorsToCollect)
	{
		const auto TargetInteraction = Cast<ICollectableInterface>(Item);
		if (!TargetInteraction) return;

		TargetInteraction->OnCollectionFinished.AddLambda(
			[this, TargetInstigator](AActor* Object, const AActor* InteractInstigator)
			{
				CollectionCount++;
				if (!CanBeCompleted || TargetInstigator != InteractInstigator || CollectionCount < CountToCollect)
					return;

				IsCompleted = true;
				OnObjectiveCompleted.Broadcast(this);
			});
	}
}
