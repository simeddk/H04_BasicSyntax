#include "CSpotLights.h"
#include "Global.h"
#include "Components/SpotLightComponent.h"
#include "CMulticast.h"

ACSpotLights::ACSpotLights()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");

	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("SpotLights");
		str.Append(FString::FromInt(i + 1));
		CHelpers::CreateSceneComponent(this, &SpotLights[i], FName(str), Root);

		SpotLights[i]->SetRelativeLocation(FVector(i * -150, 0, 0));
		SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		SpotLights[i]->Intensity = 1e+5f;
		SpotLights[i]->OuterConeAngle = 25.f;
	}
}

void ACSpotLights::BeginPlay()
{
	Super::BeginPlay();
	
	//Get Multicast Object
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACMulticast::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);
	
	ACMulticast* multiCast = Cast<ACMulticast>(actors[0]);
	CheckNull(multiCast);

	//Delegate Binding
	multiCast->OnMulticast.AddUFunction(this, "ChangeLightColor");
}

void ACSpotLights::ChangeLightColor(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
		SpotLights[i]->SetLightColor(FLinearColor(1, 1, 1));

	SpotLights[InIndex]->SetLightColor(InColor);
}