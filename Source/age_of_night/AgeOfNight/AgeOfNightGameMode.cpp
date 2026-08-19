#include "AgeOfNightGameMode.h"
#include "AgeOfNightLog.h"
#include "Engine/World.h"

AAgeOfNightGameMode::AAgeOfNightGameMode()
{
	GameStateClass = AAgeOfNightGameState::StaticClass();
}

EGamePhase AAgeOfNightGameMode::GetPhase() const
{
	if (const UWorld* World = GetWorld())
	{
		if (const AAgeOfNightGameState* AgeOfNightGameState = World->GetGameState<AAgeOfNightGameState>())
		{
			return AgeOfNightGameState->GetPhase();
		}
	}

	// InitGameState runs before any actor's BeginPlay, so a missing GameState is not a state -
	// it means GameStateClass is misconfigured. Loud, never silent.
	UE_LOG(LogAgeOfNight, Error, TEXT("No AAgeOfNightGameState; GameStateClass is misconfigured. Reporting Day."));
	return EGamePhase::Day;
}

void AAgeOfNightGameMode::SetPhase(EGamePhase NewPhase)
{
	if (const UWorld* World = GetWorld())
	{
		if (AAgeOfNightGameState* AgeOfNightGameState = World->GetGameState<AAgeOfNightGameState>())
		{
			AgeOfNightGameState->SetPhase(NewPhase);
			return;
		}
	}

	UE_LOG(LogAgeOfNight, Error, TEXT("SetPhase found no AAgeOfNightGameState; phase unchanged."));
}

void AAgeOfNightGameMode::TogglePhase()
{
	SetPhase(GetPhase() == EGamePhase::Day ? EGamePhase::Night : EGamePhase::Day);
}
