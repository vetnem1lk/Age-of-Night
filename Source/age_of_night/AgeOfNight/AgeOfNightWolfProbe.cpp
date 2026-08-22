#include "AgeOfNightWolfProbe.h"

#include "AgeOfNightLog.h"
#include "Animation/AnimSequence.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AAgeOfNightWolfProbe::AAgeOfNightWolfProbe()
{
	PrimaryActorTick.bCanEverTick = true;

	// Moves with no controller at all (verified CMC escape hatch, spec D7).
	GetCharacterMovement()->bRunPhysicsWithNoController = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	bUseControllerRotationYaw = false;

	// Anti-shove (M1b gate): no Pawn-vs-Pawn block -> no depenetration displacement;
	// overlap kept for a later bite. Spec D7.
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AAgeOfNightWolfProbe::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = ChargeSpeed;
	if (WalkAnim)
	{
		GetMesh()->PlayAnimation(WalkAnim, true);
	}
	else
	{
		UE_LOG(LogAgeOfNight, Error, TEXT("WolfProbe: WalkAnim not set on %s"), *GetName());
	}
}

void AAgeOfNightWolfProbe::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bAttacking)
	{
		// Single-node playback flips IsPlaying() to false at the one-shot's end (verified).
		if (!GetMesh()->IsPlaying())
		{
			bAttacking = false;
			if (WalkAnim)
			{
				GetMesh()->PlayAnimation(WalkAnim, true);
			}
		}
		return;
	}

	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn)
	{
		return;
	}

	FVector ToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	ToPlayer.Z = 0.f;
	const double DistanceToPlayer = ToPlayer.Size();

	if (DistanceToPlayer <= AttackRange && AttackAnim)
	{
		bAttacking = true;
		GetMesh()->PlayAnimation(AttackAnim, false);
		return;
	}

	AddMovementInput(ToPlayer.GetSafeNormal());
}
