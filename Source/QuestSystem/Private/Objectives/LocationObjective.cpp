#include "Objectives/LocationObjective.h"
#include "Core/LocationMarkerInterface.h"

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Location;
}

void ULocationObjective::ActivateObjective(AActor* TargetInstigator)
{
	Super::ActivateObjective(TargetInstigator);

	const auto TargetInteraction = Cast<ILocationMarkerInterface>(Target);
	if (!TargetInteraction) return;

	TargetInteraction->OnLocationReached.AddLambda(
		[this, TargetInstigator](AActor* Object, const AActor* InteractInstigator)
		{
			if (!CanBeCompleted || TargetInstigator != InteractInstigator) return;

			IsCompleted = true;
			OnObjectiveCompleted.Broadcast(this);
		});
}
