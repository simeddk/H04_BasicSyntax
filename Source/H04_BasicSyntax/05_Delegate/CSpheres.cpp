#include "CSpheres.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"
#include "CMulticast.h"

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
	
	//Get Multicast Object
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACMulticast::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);
	
	ACMulticast* multiCast = Cast<ACMulticast>(actors[0]);
	CheckNull(multiCast);

	//Delegate Binding
	multiCast->OnMulticast.AddUFunction(this, "Falling");

	//Create Dynamic Material
	UMaterialInstanceConstant* materialAsset;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&materialAsset, TEXT("MaterialInstanceConstant'/Game/StaticMeshes/MAT_StaticMesh_Inst.MAT_StaticMesh_Inst'"));
		
	//Set OriginLocation & Set Dynamic Materials
	for (int32 i = 0; i < 3; i++)
	{
		FTransform transform = Spheres[i]->GetComponentToWorld();
		OriginLocation[i] = transform.GetLocation();

		DynamicMaterials[i] = UMaterialInstanceDynamic::Create(materialAsset, nullptr);
		Spheres[i]->SetMaterial(0, DynamicMaterials[i]);
	}
}

void ACSpheres::Falling(int32 InIndex, FLinearColor InColor)
{
	CLog::Print("Index : " + FString::FromInt(InIndex));

	for (int32 i = 0; i < 3; i++)
	{
		Spheres[i]->SetSimulatePhysics(false);
		Spheres[i]->SetWorldLocation(OriginLocation[i]);

		DynamicMaterials[i]->SetVectorParameterValue("BaseColor", FLinearColor(1, 1, 1));
	}

	Spheres[InIndex]->SetSimulatePhysics(true);
	DynamicMaterials[InIndex]->SetVectorParameterValue("BaseColor", InColor);
}