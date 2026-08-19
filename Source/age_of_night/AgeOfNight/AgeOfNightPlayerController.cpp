#include "AgeOfNightPlayerController.h"
#include "AgeOfNightGameMode.h"
#include "AgeOfNightLog.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

namespace
{
	/** A switch rather than a ternary: adding an enumerator then trips -Wswitch instead of lying. */
	const TCHAR* PhaseToText(EGamePhase Phase)
	{
		switch (Phase)
		{
		case EGamePhase::Day:	return TEXT("Day");
		case EGamePhase::Night:	return TEXT("Night");
		}

		return TEXT("<unknown>");
	}
}

void AAgeOfNightPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Two steps, and the order matters. The current phase is never broadcast, so read it first
	// and subscribe second; binding alone would leave this controller blind until the first flip.
	if (AAgeOfNightGameState* GameState = GetWorld()->GetGameState<AAgeOfNightGameState>())
	{
		HandlePhaseChanged(GameState->GetPhase());
		GameState->OnPhaseChanged.AddDynamic(this, &AAgeOfNightPlayerController::HandlePhaseChanged);
	}
	else
	{
		UE_LOG(LogAgeOfNight, Error, TEXT("PlayerController found no AAgeOfNightGameState at BeginPlay."));
	}
}

void AAgeOfNightPlayerController::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	if (const UWorld* World = GetWorld())
	{
		if (AAgeOfNightGameState* GameState = World->GetGameState<AAgeOfNightGameState>())
		{
			GameState->OnPhaseChanged.RemoveDynamic(this, &AAgeOfNightPlayerController::HandlePhaseChanged);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void AAgeOfNightPlayerController::TogglePhase()
{
	if (AAgeOfNightGameMode* GameMode = GetWorld()->GetAuthGameMode<AAgeOfNightGameMode>())
	{
		GameMode->TogglePhase();
		return;
	}

	UE_LOG(LogAgeOfNight, Error, TEXT("TogglePhase found no AAgeOfNightGameMode; GlobalDefaultGameMode may be wrong."));
}

void AAgeOfNightPlayerController::HandlePhaseChanged(EGamePhase NewPhase)
{
	UE_LOG(LogAgeOfNight, Log, TEXT("Phase=%s"), PhaseToText(NewPhase));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan,
			FString::Printf(TEXT("Phase=%s"), PhaseToText(NewPhase)));
	}
}
