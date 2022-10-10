#pragma once

#include "CoreMinimal.h"
#include "Core/InteractionActor.h"
#include "QuestGiver.generated.h"

class AQuest;
UCLASS()
class QUESTSYSTEM_API AQuestGiver : public AInteractionActor
{
	GENERATED_BODY()

protected:
	TMap<FString, AQuest*> CachedQuests;
	
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Serialize(FArchive& Ar) override;
};
