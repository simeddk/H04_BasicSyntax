#include "CActorOverlap.h"
#include "Global.h"

void ACActorOverlap::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACActorOverlap::OnBeginOverlap);
}

void ACActorOverlap::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CLog::Log(OtherActor->GetActorLabel() + " is come in");
}
