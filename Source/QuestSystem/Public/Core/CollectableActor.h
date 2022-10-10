#pragma once

#include "CoreMinimal.h"
#include "CollectableInterface.h"
#include "GameFramework/Actor.h"
#include "CollectableActor.generated.h"

UCLASS()
class QUESTSYSTEM_API ACollectableActor : public AActor, public ICollectableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnCollectionFinished(AActor* TargetInstigator);
};
