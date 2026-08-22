#include "AgeOfNightRoutePreview.h"

#include "AgeOfNightLog.h"
#include "AgeOfNightNavFilters.h"
#include "DrawDebugHelpers.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

AAgeOfNightRoutePreview::AAgeOfNightRoutePreview()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAgeOfNightRoutePreview::BeginPlay()
{
	Super::BeginPlay();

	if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
	{
		NavSys->OnNavigationGenerationFinishedDelegate.AddDynamic(
			this, &AAgeOfNightRoutePreview::HandleNavGenerationFinished);
	}
	else
	{
		UE_LOG(LogAgeOfNight, Error, TEXT("RoutePreview: no navigation system in world"));
	}
	Requery();
}

void AAgeOfNightRoutePreview::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
	{
		NavSys->OnNavigationGenerationFinishedDelegate.RemoveDynamic(
			this, &AAgeOfNightRoutePreview::HandleNavGenerationFinished);
	}
	Super::EndPlay(EndPlayReason);
}

void AAgeOfNightRoutePreview::HandleNavGenerationFinished(ANavigationData* NavData)
{
	UE_LOG(LogAgeOfNight, Log, TEXT("RoutePreview: GenerationFinished (%s)"), *GetNameSafe(NavData));
	Requery();
}

void AAgeOfNightRoutePreview::Requery()
{
	if (!StartMarker || !GoalMarker)
	{
		UE_LOG(LogAgeOfNight, Error, TEXT("RoutePreview: Start/Goal marker not set"));
		return;
	}

	CurrentPath = UNavigationSystemV1::FindPathToLocationSynchronously(
		this,
		StartMarker->GetActorLocation(),
		GoalMarker->GetActorLocation(),
		/*PathfindingContext*/ nullptr,          // one nav agent project-wide: default nav data is correct
		UNavFilter_Wolf::StaticClass());          // invariant I3: every wolf query names this class

	++RequerySeq;
	const bool bValid = CurrentPath && CurrentPath->IsValid();
	const double PathCost = (bValid && CurrentPath->GetPath().IsValid())
		? CurrentPath->GetPath()->GetCost() : -1.0;
	UE_LOG(LogAgeOfNight, Log,
		TEXT("RoutePreview: requery %d valid=%s partial=%s cost=%.1f points=%d"),
		RequerySeq,
		bValid ? TEXT("true") : TEXT("false"),
		(bValid && CurrentPath->IsPartial()) ? TEXT("true") : TEXT("false"),
		PathCost,
		bValid ? CurrentPath->PathPoints.Num() : 0);
}

void AAgeOfNightRoutePreview::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (StartMarker)
	{
		DrawDebugSphere(GetWorld(), StartMarker->GetActorLocation(), 40.f, 12, FColor::Cyan);
	}
	if (GoalMarker)
	{
		DrawDebugSphere(GetWorld(), GoalMarker->GetActorLocation(), 40.f, 12, FColor::Yellow);
	}
	if (!CurrentPath || !CurrentPath->IsValid())
	{
		return;
	}

	const FColor RibbonColor = CurrentPath->IsPartial() ? FColor::Red : FColor::Green;
	const TArray<FVector>& Points = CurrentPath->PathPoints;
	for (int32 Index = 1; Index < Points.Num(); ++Index)
	{
		DrawDebugLine(GetWorld(),
			Points[Index - 1] + FVector(0, 0, 30),
			Points[Index] + FVector(0, 0, 30),
			RibbonColor, false, -1.f, 0, RibbonThickness);
	}
}
