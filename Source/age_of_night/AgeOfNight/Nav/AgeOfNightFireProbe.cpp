#include "AgeOfNightFireProbe.h"

#include "AgeOfNightNavAreas.h"
#include "DrawDebugHelpers.h"
#include "NavModifierComponent.h"

AAgeOfNightFireProbe::AAgeOfNightFireProbe()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SceneRoot->SetMobility(EComponentMobility::Movable);
	SetRootComponent(SceneRoot);

	NavModifier = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier"));
	NavModifier->AreaClass = UNavArea_Fire::StaticClass();
	// 800 uu across-lane: spans a 500-wide test-map lane with ±185 uu drag slack (post agent-radius
	// erosion), so a hand-dropped probe cannot leave a skirtable gap inside the lane.
	NavModifier->FailsafeExtent = FVector(250.f, 400.f, 200.f);
}

void AAgeOfNightFireProbe::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	DrawDebugBox(GetWorld(), GetActorLocation(), NavModifier->FailsafeExtent,
		FColor(255, 120, 0), false, -1.f, 0, 6.f);
}
