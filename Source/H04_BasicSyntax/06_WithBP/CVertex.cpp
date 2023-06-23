#include "CVertex.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"

ACVertex::ACVertex()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh", Root);

	UStaticMesh* meshAsset;
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Cylinder.SM_Cylinder'");
	Mesh->SetStaticMesh(meshAsset);

	UMaterialInstanceConstant* materialAsset;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&materialAsset, "MaterialInstanceConstant'/Game/StaticMeshes/MAT_StaticMesh_Inst.MAT_StaticMesh_Inst'");
	Mesh->SetMaterial(0, materialAsset);

	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 2.5f));
}

void ACVertex::BeginPlay()
{
	Super::BeginPlay();
	
}

