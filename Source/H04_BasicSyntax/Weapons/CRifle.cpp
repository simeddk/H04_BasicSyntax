#include "CRifle.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
#include "IRifle.h"
#include "Characters/CPlayer.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "SkeletalMesh'/Game/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");

	Mesh->SetSkeletalMesh(meshAsset);

	CHelpers::GetAsset(&GrabMontage, "AnimMontage'/Game/Character/Montages/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	CHelpers::GetAsset(&UngrabMontage, "AnimMontage'/Game/Character/Montages/Rifle_Ungrab_Montage.Rifle_Ungrab_Montage'");

	CHelpers::GetClass(&CameraShakeClass, "Blueprint'/Game/Player/BP_FireShake.BP_FireShake_C'");
}

ACRifle* ACRifle::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters param;
	param.Owner = InOwner;
	return InWorld->SpawnActor<ACRifle>(param);
}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket
	);
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bAiming);

	//Get Aim Information
	IIRifle* rifleCharacter = Cast<IIRifle>(OwnerCharacter);
	CheckNull(rifleCharacter);

	FVector start, end, direction;
	rifleCharacter->GetAimInfo(start, end, direction);

	//LineTrace(AimWidget)
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	param.AddIgnoredActor(OwnerCharacter);

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel
	(
		hitResult,
		start,
		end,
		ECollisionChannel::ECC_PhysicsBody,
		param
	))
	{
		OtherActor = Cast<AStaticMeshActor>(hitResult.GetActor());

		if (!!OtherActor)
		{
			UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(OtherActor->GetRootComponent());
			if (!!meshComp)
			{
				if (meshComp->IsSimulatingPhysics())
				{
					rifleCharacter->OnTarget();
					return;
				}
			}
		}

		rifleCharacter->OffTarget();
	}


}

void ACRifle::Equip()
{
	CheckTrue(bEquipped);
	CheckTrue(bEquipping);

	OwnerCharacter->PlayAnimMontage(GrabMontage);
	bEquipping = true;
}

void ACRifle::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSocket
	);
}

void ACRifle::End_Equip()
{
	bEquipping = false;
}

void ACRifle::Unequip()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

	OwnerCharacter->PlayAnimMontage(UngrabMontage);
	bEquipping = true;
}

void ACRifle::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket
	);
}

void ACRifle::End_Unequip()
{
	bEquipping = false;
}

void ACRifle::Begin_Aim()
{
	bAiming = true;
}

void ACRifle::End_Aim()
{
	bAiming = false;
}

void ACRifle::Begin_Fire()
{
	CheckFalse(bEquipped);
	CheckFalse(bAiming);
	CheckTrue(bEquipping);
	CheckTrue(bFiring);

	bFiring = true;

	Firing();
}

void ACRifle::End_Fire()
{
	bFiring = false;
}

void ACRifle::Firing()
{
	//Play CameraShake
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	if (!!player)
	{
		APlayerController* controller = player->GetController<APlayerController>();
		if (!!controller)
			controller->PlayerCameraManager->PlayCameraShake(CameraShakeClass);
	}

	//Todo. Spawn Bullet
	//GetWorld()->SpawnActor<>(BP_ClassRef, MuzzleFlashSocketWS, CameraDir)

	//Add Impluse
	CheckNull(OtherActor);
	UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(OtherActor->GetRootComponent());
	if (!!meshComp)
	{
		if (meshComp->BodyInstance.bSimulatePhysics == true)
		{
			FVector direction = OtherActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
			direction.Normalize();

			FVector force = direction * 3000.f;

			meshComp->AddImpulseAtLocation(force, OwnerCharacter->GetActorLocation());
			return;
		}
	}
}
