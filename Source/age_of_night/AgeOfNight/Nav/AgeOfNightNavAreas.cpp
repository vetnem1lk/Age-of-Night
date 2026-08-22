#include "AgeOfNightNavAreas.h"

UNavArea_Fire::UNavArea_Fire()
{
	DefaultCost = 10.f;
	FixedAreaEnteringCost = 2500.f;   // protected on UNavArea; settable from a subclass ctor
	DrawColor = FColor(255, 120, 0);
}
