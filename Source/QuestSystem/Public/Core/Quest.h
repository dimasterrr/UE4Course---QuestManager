#pragma once

#include "CoreMinimal.h"
#include "Quest.generated.h"

class UObjective;
UENUM()
enum class EQuestType : uint8
{
	Story,
	Advanced
};

UCLASS()
class QUESTSYSTEM_API AQuest : public AActor
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestStatusChanged, AQuest*)

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EQuestType QuestType = EQuestType::Story;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ValidateOrder = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsTaken = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UObjective*> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AQuest* PrerequisiteQuest = nullptr;

	FOnQuestStatusChanged OnQuestStatusChanged;

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Serialize(FArchive& Ar) override;

	UFUNCTION()
	void TakeQuest(AActor* TargetInstigator);

	UFUNCTION(BlueprintCallable)
	bool IsCompleted() const;

	void OnObjectiveCompleted(UObjective* Objective);

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateLocation();

	UFUNCTION(CallInEditor)
	void AddInteractObjective();

	UFUNCTION(CallInEditor)
	void AddLocationObjective();

	UFUNCTION(CallInEditor)
	void AddCollectionObjective();
#endif
};
