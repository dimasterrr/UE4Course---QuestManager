#pragma once

#include "CoreMinimal.h"
#include "Core/Objective.h"
#include "CollectionObjective.generated.h"

UCLASS()
class QUESTSYSTEM_API UCollectionObjective final : public UObjective
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> CollectableActorClass;

	UPROPERTY(EditAnywhere)
	int32 CountToCollect = 1;

	UPROPERTY(VisibleAnywhere)
	int32 CollectionCount = 0;
	
public:
	UCollectionObjective();
	
	virtual void ActivateObjective(AActor* TargetInstigator) override;
};
