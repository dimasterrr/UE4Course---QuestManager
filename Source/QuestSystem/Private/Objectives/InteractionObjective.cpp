#include "Objectives/InteractionObjective.h"

#include "Core/InteractionActor.h"
#include "Core/InteractionInterface.h"

UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Interact;
}

void UInteractionObjective::ActivateObjective(AActor* TargetInstigator)
{
	Super::ActivateObjective(TargetInstigator);

	const auto TargetInteraction = Cast<AInteractionActor>(Target);
	if (!TargetInteraction) return;
	
	TargetInteraction->OnInteractionFinished.AddLambda(
		[this, TargetInstigator](AActor* Object, const AActor* InteractInstigator)
		{
			if (!CanBeCompleted || TargetInstigator != InteractInstigator) return;
	
			IsCompleted = true;
			OnObjectiveCompleted.Broadcast(this);
		});
}
