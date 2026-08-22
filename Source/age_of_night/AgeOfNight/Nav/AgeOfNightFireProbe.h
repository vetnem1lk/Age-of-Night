#pragma once

#include "GameFramework/Actor.h"
#include "AgeOfNightFireProbe.generated.h"

class UNavModifierComponent;

/**
 * Movable carrier for a UNavArea_Fire nav modifier. No collision on purpose: the modifier stamps
 * FailsafeExtent (spec D3), and under DynamicModifiersOnly runtime geometry never rebuilds anyway.
 * Moved in PIE via F8 eject + gizmo.
 */
UCLASS()
class AGE_OF_NIGHT_API AAgeOfNightFireProbe : public AActor
{
	GENERATED_BODY()

public:
	AAgeOfNightFireProbe();

	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Fire")
	TObjectPtr<UNavModifierComponent> NavModifier;
};
