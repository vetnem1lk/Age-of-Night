#include "Misc/AutomationTest.h"
#include "AgeOfNightGameState.h"
#include "AgeOfNightPhaseTestListener.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAgeOfNightPhaseTest,
	"AgeOfNight.Phase.SetPhaseBroadcastsOnceAndIsIdempotent",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FAgeOfNightPhaseTest::RunTest(const FString& Parameters)
{
	AAgeOfNightGameState* GameState = NewObject<AAgeOfNightGameState>(GetTransientPackage());
	UAgeOfNightPhaseTestListener* Listener = NewObject<UAgeOfNightPhaseTestListener>(GetTransientPackage());

	GameState->OnPhaseChanged.AddDynamic(Listener, &UAgeOfNightPhaseTestListener::OnPhaseChanged);

	TestEqual(TEXT("starts in Day"), static_cast<int32>(GameState->GetPhase()), static_cast<int32>(EGamePhase::Day));
	TestEqual(TEXT("nothing broadcast before a change"), Listener->CallCount, 0);

	GameState->SetPhase(EGamePhase::Night);
	TestEqual(TEXT("phase became Night"), static_cast<int32>(GameState->GetPhase()), static_cast<int32>(EGamePhase::Night));
	TestEqual(TEXT("one broadcast"), Listener->CallCount, 1);
	TestEqual(TEXT("broadcast carried Night"), static_cast<int32>(Listener->LastPhase), static_cast<int32>(EGamePhase::Night));

	GameState->SetPhase(EGamePhase::Night);
	TestEqual(TEXT("the same phase broadcasts nothing"), Listener->CallCount, 1);

	GameState->SetPhase(EGamePhase::Day);
	TestEqual(TEXT("returning to Day broadcasts again"), Listener->CallCount, 2);
	TestEqual(TEXT("phase became Day"), static_cast<int32>(GameState->GetPhase()), static_cast<int32>(EGamePhase::Day));

	return true;
}

#endif
