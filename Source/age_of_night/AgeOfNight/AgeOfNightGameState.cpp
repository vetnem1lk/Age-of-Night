#include "AgeOfNightGameState.h"

void AAgeOfNightGameState::SetPhase(EGamePhase NewPhase)
{
	if (NewPhase == Phase)
	{
		return;
	}

	Phase = NewPhase;
	OnPhaseChanged.Broadcast(Phase);
}
