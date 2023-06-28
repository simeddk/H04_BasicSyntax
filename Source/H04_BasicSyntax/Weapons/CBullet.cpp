#include "CBullet.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACBullet::ACBullet()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");
	
	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "/Game/StaticMeshes/SM_Sphere");
	Mesh->SetStaticMesh(meshAsset);

	UMaterialInstanceConstant* materialAsset;
	CHelpers::GetAsset(&materialAsset, "/Game/Weapons/MAT_Bullet_Inst");
	Mesh->SetMaterial(0, materialAsset);

	Mesh->SetRelativeScale3D(FVector(1.f, 0.025f, 0.025f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Projectile->ProjectileGravityScale = 0.f;
	Projectile->InitialSpeed = 2e+4f;
	Projectile->MaxSpeed = 2e+4f;
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.f);
}

