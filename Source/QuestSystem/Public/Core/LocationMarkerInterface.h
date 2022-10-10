#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LocationMarkerInterface.generated.h"

UINTERFACE()
class ULocationMarkerInterface : public UInterface
{
	GENERATED_BODY()
};

class QUESTSYSTEM_API ILocationMarkerInterface
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLocationReached, AActor*, AActor*)

public:
	FOnLocationReached OnLocationReached;

public:
	virtual void OverlapWithActor(AActor* TargetMarker, AActor* OverlappedActor);
};
