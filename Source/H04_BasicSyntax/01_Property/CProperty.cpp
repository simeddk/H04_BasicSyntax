#include "CProperty.h"

ACProperty::ACProperty()
{
	PrimaryActorTick.bCanEverTick = true;

	NumA = 100;
	NumB = 200;
	NumC = 300;

	//AActor* testActor = nullptr;
	//GLog->Log(testActor->GetName());
}

void ACProperty::BeginPlay()
{
	Super::BeginPlay();

	FString str;
	str.Append("NumA : ");
	str.Append(FString::FromInt(NumA));
	str.Append(", RealA : ");
	str.Append(FString::SanitizeFloat(RealA));

	GLog->Log(str);
}

void ACProperty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

