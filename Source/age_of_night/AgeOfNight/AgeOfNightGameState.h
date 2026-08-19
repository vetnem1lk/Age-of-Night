#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AgeOfNightGameState.generated.h"

/**
 *  Which half of the loop is running. Day is the zero value on purpose: the game starts in Day,
 *  so "not yet initialised" and "Day" must be the same observable state. No None member.
 */
UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	Day,
	Night
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, EGamePhase, NewPhase);

/**
 *  Holds the run's phase. Read by anyone, written only by AAgeOfNightGameMode.
 *
 *  Not replicated: the slice is single player. If multiplayer ever appears, Phase becomes
 *  ReplicatedUsing = OnRep_Phase and the broadcast moves into OnRep_Phase. Living here rather
 *  than on the GameMode is what keeps that a small change - the GameMode has no client instance.
 */
UCLASS()
class AGE_OF_NIGHT_API AAgeOfNightGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	/**
	 *  Fired after the phase changes. Never fired for the initial value, so a subscriber reads
	 *  GetPhase() first and binds second - otherwise anything binding late sits in an unknown state.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Age of Night|Phase")
	FOnPhaseChanged OnPhaseChanged;

	/** The current phase. Always readable. */
	UFUNCTION(BlueprintPure, Category = "Age of Night|Phase")
	EGamePhase GetPhase() const { return Phase; }

	/**
	 *  Sets the phase and broadcasts. Idempotent: the same value writes nothing and broadcasts
	 *  nothing, so wave boundaries cannot re-trigger every subscriber.
	 *
	 *  Authored by AAgeOfNightGameMode only. Deliberately not BlueprintCallable.
	 */
	void SetPhase(EGamePhase NewPhase);

private:

	EGamePhase Phase = EGamePhase::Day;
};
