#include "CPointLights.h"
#include "Global.h"
#include "CDelegate.h"
#include "Components/PointLightComponent.h"

ACPointLights::ACPointLights()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &PointLight1, "PointLight1", Root);
	CHelpers::CreateSceneComponent(this, &PointLight2, "PointLight2", Root);

	PointLight1->SetIntensity(1e+4f);
	PointLight1->SetAttenuationRadius(200.f);
	PointLight1->SetLightColor(FLinearColor(1.f, 0.5f, 0.2f));

	PointLight2->SetIntensity(1e+4f);
	PointLight2->SetAttenuationRadius(200.f);
	PointLight2->SetLightColor(FLinearColor(1.f, 0.5f, 0.2f));
	PointLight2->SetRelativeLocation(FVector(200.f, 0, 0));
}

void ACPointLights::BeginPlay()
{
	Super::BeginPlay();
	
	PointLight1->SetVisibility(false);
	PointLight2->SetVisibility(false);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACDelegate::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACDelegate* delegateObject = Cast<ACDelegate>(actors[0]);
	CheckNull(delegateObject);

	delegateObject->OnBoxBeginOverlap.BindUFunction(this, "On");
	delegateObject->OnBoxEndOverlap.BindUFunction(this, "Off");

	delegateObject->OnRandomBeginOverlap.BindUFunction(this, "OnRandomLight");
}

void ACPointLights::On()
{
	PointLight1->SetVisibility(true);
}

void ACPointLights::Off()
{
	PointLight1->SetVisibility(false);
	PointLight2->SetVisibility(false);
}

FString ACPointLights::OnRandomLight(FLinearColor InColor)
{
	PointLight2->SetVisibility(true);
	PointLight2->SetLightColor(InColor);

	return InColor.ToString();
}

