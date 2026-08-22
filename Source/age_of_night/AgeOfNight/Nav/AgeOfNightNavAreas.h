#pragma once

#include "NavAreas/NavArea.h"
#include "AgeOfNightNavAreas.generated.h"

/**
 * Fire: expensive to cross, very expensive to enter, never impassable (spec invariant I5).
 * All three knobs are config — tune in DefaultEngine.ini under
 * [/Script/age_of_night.NavArea_Fire], no recompile.
 */
UCLASS(Config = Engine)
class AGE_OF_NIGHT_API UNavArea_Fire : public UNavArea
{
	GENERATED_BODY()

public:
	UNavArea_Fire();
};
