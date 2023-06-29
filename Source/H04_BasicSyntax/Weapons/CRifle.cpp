#include "CRifle.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/DecalComponent.h"
#include "IRifle.h"
#include "Characters/CPlayer.h"
#include "CBullet.h" 

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
	CHelpers::GetClass(&BulletClass, "/Game/Weapons/BP_CBullet");

	CHelpers::GetAsset(&FlashParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	CHelpers::GetAsset(&EjectParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	CHelpers::GetAsset(&ImpactParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");
	CHelpers::GetAsset(&FireSoundCue, "SoundCue'/Game/Sounds/S_RifleShoot_Cue.S_RifleShoot_Cue'");

	CHelpers::GetAsset(&Decal, "MaterialInstanceConstant'/Game/Materials/M_Decal_Inst.M_Decal_Inst'");
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

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
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

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
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
	//CheckFalse(bAiming);
	CheckTrue(bEquipping);
	CheckTrue(bFiring);

	bFiring = true;

	Pitch = 0.f;

	if (bRepeat == true)
	{
		GetWorld()->GetTimerManager().SetTimer(RepeatTimer, this, &ACRifle::Firing, 0.1f, true);
		return;
	}

	Firing();
}

void ACRifle::End_Fire()
{
	bFiring = false;

	if (bRepeat == true)
		GetWorld()->GetTimerManager().ClearTimer(RepeatTimer);
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

	//Spawn Bullet
	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");

	IIRifle* rifleOwner = Cast<IIRifle>(OwnerCharacter);
	FVector start, end, direction;
	rifleOwner->GetAimInfo(start, end, direction);

	if (!!rifleOwner)
	{
		if (!!BulletClass)
			GetWorld()->SpawnActor<ACBullet>(BulletClass, muzzleLocation, direction.Rotation());
	}

	//Play Effects
	UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation);


	//Decrease Pitch
	Pitch -= PitchSpeed * GetWorld()->GetDeltaSeconds();
	if (Pitch > -PitchSpeed)
	{
		OwnerCharacter->AddControllerPitchInput(Pitch);
		CLog::Print(Pitch, 1);
	}

	//LineTrace(Decal & ImpactParticle)
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	param.AddIgnoredActor(OwnerCharacter);

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel
	(
		hitResult,
		start,
		end,
		ECollisionChannel::ECC_Visibility,
		param
	))
	{
		AStaticMeshActor* smActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!smActor)
		{
			FRotator decalRotation = hitResult.ImpactNormal.Rotation();
			UDecalComponent* decalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), Decal, FVector(5), hitResult.Location, decalRotation, 10.f);
			decalComp->SetFadeScreenSize(0);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, decalRotation);
		}
	}

	//Add Impluse
	CheckNull(OtherActor);
	UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(OtherActor->GetRootComponent());
	if (!!meshComp)
	{
		if (meshComp->BodyInstance.bSimulatePhysics == true)
		{
			FVector targetDirection = OtherActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
			targetDirection.Normalize();

			FVector force = targetDirection * 3000.f;

			meshComp->AddImpulseAtLocation(force, OwnerCharacter->GetActorLocation());
			return;
		}
	}
}
