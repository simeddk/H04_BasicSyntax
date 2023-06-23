#include "CSphereTrace.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"

ACSphereTrace::ACSphereTrace()
{
	CHelpers::CreateSceneComponent(this, &Particle, "Particle");

	UParticleSystem* particleAsset;
	CHelpers::GetAsset<UParticleSystem>(&particleAsset, "ParticleSystem'/Game/Particles/P_ImpactExplosion8.P_ImpactExplosion8'");
	Particle->SetTemplate(particleAsset);

	Particle->bAutoActivate = false;
}

void ACSphereTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSphereTrace::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FVector start = GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 10);

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery4);
	 
	//Todo. 스피어트레이스 마무리하기
	/*if (UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		start,
		end,
		1000.f,
		objectTypes,


	))
	{

	}*/
}

