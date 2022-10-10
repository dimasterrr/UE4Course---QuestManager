#include "Core/CollectableInterface.h"

void ICollectableInterface::CollectFinished(AActor* TargetCollection, AActor* TargetInstigator)
{
	if (!OnCollectionFinished.IsBound()) return;

	OnCollectionFinished.Broadcast(TargetCollection, TargetInstigator);
}
