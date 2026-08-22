#pragma once

#include "GameFramework/Character.h"
#include "AgeOfNightWolfProbe.generated.h"

class UAnimSequence;

/**
 * M1b probe: charge the player and lunge, no AnimBlueprint, no controller (spec D7).
 * Abstract — BP_WolfProbe supplies the skeletal mesh and the two sequences.
 */
UCLASS(abstract)
class AGE_OF_NIGHT_API AAgeOfNightWolfProbe : public ACharacter
{
	GENERATED_BODY()

public:
	AAgeOfNightWolfProbe();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Wolf")
	TObjectPtr<UAnimSequence> WalkAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Wolf")
	TObjectPtr<UAnimSequence> AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Wolf")
	float AttackRange = 250.f;

	UPROPERTY(EditAnywhere, Category = "Wolf")
	float ChargeSpeed = 550.f;

private:
	bool bAttacking = false;
};
