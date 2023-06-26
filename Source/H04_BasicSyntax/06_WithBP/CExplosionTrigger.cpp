#include "CExplosionTrigger.h"
#include "Global.h"
#include "CSphereTrace.h"

void ACExplosionTrigger::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACSphereTrace::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACSphereTrace* sphereTrace = Cast<ACSphereTrace>(actors[0]);
	CheckNull(sphereTrace);

	OnActorBeginOverlap.AddDynamic(sphereTrace, &ACSphereTrace::BeginOverlap);
}