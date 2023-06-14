#include "CStaticMesh.h"
#include "Global.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialInstanceConstant.h"

ACStaticMesh::ACStaticMesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void ACStaticMesh::BeginPlay()
{
	Super::BeginPlay();
	
	//ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> materialAsset(TEXT("MaterialInstanceConstant'/Game/StaticMeshes/MAT_StaticMesh_Inst.MAT_StaticMesh_Inst'"));
	//if (materialAsset.Succeeded()) 

	UObject* asset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/StaticMeshes/MAT_StaticMesh_Inst.MAT_StaticMesh_Inst'"));
	UMaterialInstanceConstant* materialAsset = Cast<UMaterialInstanceConstant>(asset);
	
	DynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), materialAsset);
	Mesh->SetMaterial(0, DynamicMaterial);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.f, true);
}

void ACStaticMesh::ChangeColor()
{
	float r = UKismetMathLibrary::RandomFloatInRange(0, 1);
	float g = UKismetMathLibrary::RandomFloatInRange(0, 1);
	float b = UKismetMathLibrary::RandomFloatInRange(0, 1);
	float a = 1.f;

	DynamicMaterial->SetVectorParameterValue("BaseColor", FLinearColor(r, g, b, a));
	DynamicMaterial->SetScalarParameterValue("Metallic", r);
	DynamicMaterial->SetScalarParameterValue("Roughness", r);

}

