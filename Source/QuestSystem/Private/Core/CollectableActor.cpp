#include "Core/CollectableActor.h"

void ACollectableActor::OnCollectionFinished(AActor* TargetInstigator)
{
	CollectFinished(this, TargetInstigator);
}
