#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapons/IRifle.h"
#include "Weapons/CRifle.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnwerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OnwerCharacter);

	Speed = OnwerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OnwerCharacter->GetVelocity(), OnwerCharacter->GetControlRotation());
	Pitch = OnwerCharacter->GetBaseAimRotation().Pitch;

	IIRifle* rifleCharacter = Cast<IIRifle>(OnwerCharacter);
	if (!!rifleCharacter && !!rifleCharacter->GetRifle())
	{
		bEquipped = rifleCharacter->GetRifle()->IsEquipped();
		bAiming = rifleCharacter->GetRifle()->IsAiming();
	}
}

