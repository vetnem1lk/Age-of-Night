#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AgeOfNightGameState.h"
#include "AgeOfNightPhaseTestListener.generated.h"

/** Counts OnPhaseChanged broadcasts. Exists for the automation test and nothing else. */
UCLASS()
class UAgeOfNightPhaseTestListener : public UObject
{
	GENERATED_BODY()

public:

	int32 CallCount = 0;
	EGamePhase LastPhase = EGamePhase::Day;

	UFUNCTION()
	void OnPhaseChanged(EGamePhase NewPhase)
	{
		++CallCount;
		LastPhase = NewPhase;
	}
};
