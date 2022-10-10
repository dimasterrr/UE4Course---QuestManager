#include "Core/LocationMarkerInterface.h"

void ILocationMarkerInterface::OverlapWithActor(AActor* TargetMarker, AActor* OverlappedActor)
{
	if (!OnLocationReached.IsBound()) return;

	OnLocationReached.Broadcast(TargetMarker, OverlappedActor);
}
