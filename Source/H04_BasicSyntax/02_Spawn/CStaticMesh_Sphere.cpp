#include "CStaticMesh_Sphere.h"

ACStaticMesh_Sphere::ACStaticMesh_Sphere()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/StaticMeshes/SM_Sphere.SM_Sphere'"));
	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
}