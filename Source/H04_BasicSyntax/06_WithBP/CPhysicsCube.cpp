#include "CPhysicsCube.h"
#include "Global.h"

ACPhysicsCube::ACPhysicsCube()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "/Game/StaticMeshes/SM_Cube");
	Mesh->SetStaticMesh(meshAsset);

	UMaterial* materialAsset;
	CHelpers::GetAsset<UMaterial>(&materialAsset, "Material'/Game/StaticMeshes/MAT_WoodBox.MAT_WoodBox'");
	Mesh->SetMaterial(0, materialAsset);

	Mesh->SetRelativeScale3D(FVector(0.8f));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
}

void ACPhysicsCube::BeginPlay()
{
	Super::BeginPlay();
	
}

