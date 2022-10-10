#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Objective.generated.h"

UENUM()
enum class EObjectiveType : uint8
{
	Interact,
	Location,
	Collect
};

UCLASS(Abstract)
class QUESTSYSTEM_API UObjective : public UObject
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveCompleted, UObjective*)

public:
	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	EObjectiveType Type = EObjectiveType::Location;

	UPROPERTY(VisibleAnywhere)
	bool IsCompleted = false;

	UPROPERTY(VisibleAnywhere)
	bool CanBeCompleted = true;

	FOnObjectiveCompleted OnObjectiveCompleted;

public:
	virtual void ActivateObjective(AActor* TargetInstigator);
};
