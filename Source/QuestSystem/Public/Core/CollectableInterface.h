#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollectableInterface.generated.h"

UINTERFACE()
class UCollectableInterface : public UInterface
{
	GENERATED_BODY()
};

class QUESTSYSTEM_API ICollectableInterface
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCollectionFinished, AActor*, AActor*)

public:
	FOnCollectionFinished OnCollectionFinished;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Collect (AActor* TargetInstigator);

	virtual void CollectFinished(AActor* TargetCollection, AActor* TargetInstigator);
};