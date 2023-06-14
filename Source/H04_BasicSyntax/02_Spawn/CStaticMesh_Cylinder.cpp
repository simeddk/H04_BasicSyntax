#include "CStaticMesh_Cylinder.h"

ACStaticMesh_Cylinder::ACStaticMesh_Cylinder()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/StaticMeshes/SM_Cylinder.SM_Cylinder'"));
	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
}