#pragma once

#include "CoreMinimal.h"
#include "age_of_nightGameMode.h"
#include "AgeOfNightGameState.h"
#include "AgeOfNightGameMode.generated.h"

/**
 *  The only authority over the phase. M3's Ready Up and M4's wave transitions become methods
 *  here that call SetPhase, which is why the authority sits on the GameMode from the start.
 *
 *  Abstract, per project convention: the concrete class is a Blueprint, because DefaultPawnClass
 *  and PlayerControllerClass are asset references C++ should not hard-code.
 */
UCLASS(abstract)
class AGE_OF_NIGHT_API AAgeOfNightGameMode : public Aage_of_nightGameMode
{
	GENERATED_BODY()

public:

	AAgeOfNightGameMode();

	/** The current phase. Logs an error and reports Day when the GameState is missing. */
	EGamePhase GetPhase() const;

	/** Writes the phase through the GameState, which ignores an unchanged value. */
	void SetPhase(EGamePhase NewPhase);

	/** Day to Night and back. */
	void TogglePhase();
};
