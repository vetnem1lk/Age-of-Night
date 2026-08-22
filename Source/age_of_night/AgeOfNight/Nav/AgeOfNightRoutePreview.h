#pragma once

#include "GameFramework/Actor.h"
#include "AgeOfNightRoutePreview.generated.h"

class ANavigationData;
class UNavigationPath;

/**
 * M1 kill-gate probe: draws the wolf-filtered route Start->Goal and re-solves it only after
 * navigation generation finishes (spec invariant I4). Concrete: no asset refs, spawns directly.
 */
UCLASS()
class AGE_OF_NIGHT_API AAgeOfNightRoutePreview : public AActor
{
	GENERATED_BODY()

public:
	AAgeOfNightRoutePreview();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Route")
	TObjectPtr<AActor> StartMarker;

	UPROPERTY(EditAnywhere, Category = "Route")
	TObjectPtr<AActor> GoalMarker;

	UPROPERTY(EditAnywhere, Category = "Route")
	float RibbonThickness = 10.f;

private:
	UFUNCTION()
	void HandleNavGenerationFinished(ANavigationData* NavData);

	void Requery();

	UPROPERTY()
	TObjectPtr<UNavigationPath> CurrentPath;

	int32 RequerySeq = 0;
};
