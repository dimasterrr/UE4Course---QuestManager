#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Quest.h"
#include "QuestManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUESTSYSTEM_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveQuestChanged, AQuest*, Quest);

protected:
	UPROPERTY()
	TArray<AQuest*> AcceptedQuests;

	UPROPERTY()
	AQuest* ActiveQuest;

public:
	UPROPERTY(BlueprintAssignable)
	FOnActiveQuestChanged OnActiveQuestChanged;

public:
	virtual void Serialize(FArchive& Ar) override;

	UFUNCTION(BlueprintCallable)
	void AddQuest(AQuest* Quest);

	UFUNCTION(BlueprintCallable)
	const TArray<AQuest*>& GetQuests();

	UFUNCTION(BlueprintCallable)
	AQuest* GetActiveQuest() const;

	UFUNCTION(BlueprintCallable)
	void SetActiveQuest(AQuest* Quest);
};
