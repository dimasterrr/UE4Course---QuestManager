#pragma once

#include "CoreMinimal.h"
#include "Core/Objective.h"
#include "InteractionObjective.generated.h"

UCLASS()
class QUESTSYSTEM_API UInteractionObjective final : public UObjective
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "InteractionActor"))
	AActor* Target;
	
public:
	UInteractionObjective();
	
	virtual void ActivateObjective(AActor* TargetInstigator) override;
};
