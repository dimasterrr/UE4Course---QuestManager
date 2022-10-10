#pragma once

#include "CoreMinimal.h"
#include "LocationMarkerInterface.h"
#include "GameFramework/Actor.h"
#include "LocationMarkerActor.generated.h"

UCLASS()
class QUESTSYSTEM_API ALocationMarkerActor : public AActor, public ILocationMarkerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnOverlapByActor(AActor* OverlappingActor);
};
