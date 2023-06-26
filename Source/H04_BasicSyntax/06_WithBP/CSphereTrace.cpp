#include "CSphereTrace.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

ACSphereTrace::ACSphereTrace()
{
	CHelpers::CreateSceneComponent(this, &Particle, "Particle");
	CHelpers::CreateSceneComponent(this, &Text, "Text", Particle);

	UParticleSystem* particleAsset;
	CHelpers::GetAsset<UParticleSystem>(&particleAsset, "ParticleSystem'/Game/Particles/P_AuraCircle_Default_StartUp_01.P_AuraCircle_Default_StartUp_01'");
	Particle->SetTemplate(particleAsset);
	Particle->bAutoActivate = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetTextRenderColor(FColor::Red);
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->SetText(FText::FromString(GetName()));
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
	
	TArray<AActor*> ignrores;
	TArray<FHitResult> hitResults;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		start,
		end,
		1000.f,
		objectTypes,
		false,
		ignrores,
		EDrawDebugTrace::ForDuration,
		hitResults,
		true
	))
	{
		Particle->ResetParticles();
		Particle->SetActive(true);

		for (const FHitResult& hitResult : hitResults)
		{
			UStaticMeshComponent* meshComp =
				Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());

			if (!!meshComp)
			{
				meshComp->AddRadialImpulse
				(
					GetActorLocation(),
					1000.f,
					15e+6f / meshComp->GetMass(),
					ERadialImpulseFalloff::RIF_Linear
				);
			}
		}
	}
}

