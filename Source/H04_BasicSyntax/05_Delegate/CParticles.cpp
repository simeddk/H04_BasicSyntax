#include "CParticles.h"
#include "Global.h"
#include "CEvent.h"
#include "Particles/ParticleSystem.h"

ACParticles::ACParticles()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");

	CHelpers::GetAsset<UParticleSystem>(&Particles[0], "ParticleSystem'/Game/Particles/P_ImpactExplosion8.P_ImpactExplosion8'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[1], "ParticleSystem'/Game/Particles/P_Genno_Weapon_Lightning_01.P_Genno_Weapon_Lightning_01'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[2], "ParticleSystem'/Game/Particles/P_AuraCircle_Default_StartUp_01.P_AuraCircle_Default_StartUp_01'");
}

void ACParticles::BeginPlay()
{
	Super::BeginPlay();
	
	//Get Multicast Object
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACEvent::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACEvent* eventObj = Cast<ACEvent>(actors[0]);
	CheckNull(eventObj);

	eventObj->OnEvent.AddUFunction(this, "Play");
}

void ACParticles::Play(int32 InIndex)
{
	FTransform transform;
	transform.SetLocation(GetActorLocation());


	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], transform);
}

