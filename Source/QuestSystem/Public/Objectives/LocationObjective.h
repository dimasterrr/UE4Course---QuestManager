#pragma once

#include "CoreMinimal.h"
#include "Core/Objective.h"
#include "LocationObjective.generated.h"

UCLASS()
class QUESTSYSTEM_API ULocationObjective final : public UObjective
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "LocationMarkerActor"))
	AActor* Target;
	
public:
	ULocationObjective();
	
	virtual void ActivateObjective(AActor* TargetInstigator) override;
};
