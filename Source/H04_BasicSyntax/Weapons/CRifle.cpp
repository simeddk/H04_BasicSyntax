#include "CRifle.h"
#include "Global.h"
#include "GameFramework/Character.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "SkeletalMesh'/Game/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");

	Mesh->SetSkeletalMesh(meshAsset);

	CHelpers::GetAsset(&GrabMontage, "AnimMontage'/Game/Character/Montages/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	CHelpers::GetAsset(&UngrabMontage, "AnimMontage'/Game/Character/Montages/Rifle_Ungrab_Montage.Rifle_Ungrab_Montage'");
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
	bEquipping = false; //Todo. bEquipped -> bEquipping
}

void ACRifle::Unequip()
{

}