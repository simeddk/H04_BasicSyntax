#include "CComponentOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"

ACComponentOverlap::ACComponentOverlap()
{
	CHelpers::CreateSceneComponent(this, &PointLight, "PointLight", Root);

	PointLight->SetLightColor(FLinearColor::Red);
}

void ACComponentOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility(false);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACComponentOverlap::BeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACComponentOverlap::EndOverlap);
}

void ACComponentOverlap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLight->SetVisibility(true);
}

void ACComponentOverlap::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLight->SetVisibility(false);
}
