#include "Core/LocationMarkerActor.h"

void ALocationMarkerActor::OnOverlapByActor(AActor* OverlappingActor)
{
	OverlapWithActor(this, OverlappingActor);
}