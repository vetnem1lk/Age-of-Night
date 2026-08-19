#pragma once

#include "CoreMinimal.h"
#include "age_of_nightPlayerController.h"
#include "AgeOfNightGameState.h"
#include "AgeOfNightPlayerController.generated.h"

/**
 *  First subscriber to the phase, and owner of the debug toggle.
 *
 *  It subscribes here rather than in a throwaway actor because M2 needs exactly this class to
 *  swap Input Mapping Contexts per phase - so nothing built here is discarded.
 */
UCLASS(abstract)
class AGE_OF_NIGHT_API AAgeOfNightPlayerController : public Aage_of_nightPlayerController
{
	GENERATED_BODY()

public:

	/** Debug only: flips the phase. Console command: TogglePhase */
	UFUNCTION(Exec)
	void TogglePhase();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/** The only thing that logs a phase on the happy path, so one press means one line. */
	UFUNCTION()
	void HandlePhaseChanged(EGamePhase NewPhase);
};
