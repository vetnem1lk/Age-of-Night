#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AgeOfNightGameState.h"
#include "AgeOfNightPhaseTestListener.generated.h"

/** Counts OnPhaseChanged broadcasts. Exists for the automation test and nothing else. */
// Note: UCLASS cannot be inside #if WITH_DEV_AUTOMATION_TESTS (UHT restriction) — the engine's own
// test UCLASSes are unguarded for the same reason (see SSAMTestTypes.h). Stripping this listener
// from Shipping would need an editor-only module; not worth it for one small listener.
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
