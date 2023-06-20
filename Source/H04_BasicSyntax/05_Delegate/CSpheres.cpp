#include "CSpheres.h"
#include "Global.h"

ACSpheres::ACSpheres()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");


	UStaticMesh* meshAssetObject = nullptr;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/StaticMeshes/SM_Sphere.SM_Sphere'"));
	if (meshAsset.Succeeded())
		meshAssetObject = meshAsset.Object;

	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("Sphere");
		str.Append(FString::FromInt(i + 1));
		CHelpers::CreateSceneComponent(this, &Spheres[i], FName(str), Root);

		Spheres[i]->SetStaticMesh(meshAssetObject);
		Spheres[i]->SetRelativeLocation(FVector(i * -150, 0, 0));
	}
}

void ACSpheres::BeginPlay()
{
	Super::BeginPlay();
	
}

