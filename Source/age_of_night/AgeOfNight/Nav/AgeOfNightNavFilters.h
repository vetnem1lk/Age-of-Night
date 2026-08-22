#pragma once

#include "NavFilters/NavigationQueryFilter.h"
#include "AgeOfNightNavFilters.generated.h"

/**
 * The one filter every wolf path query names (spec invariant I3): the route preview now,
 * DefaultNavigationFilterClass and EQS PathCost at M4. Empty on purpose — with no overrides it
 * inherits UNavArea defaults; M6 adds Lit/Unlit variants. Do not add overrides without a second
 * consumer, and remember: filter travel-cost overrides clamp at 1.0 (spec correction 6).
 */
UCLASS()
class AGE_OF_NIGHT_API UNavFilter_Wolf : public UNavigationQueryFilter
{
	GENERATED_BODY()
};
