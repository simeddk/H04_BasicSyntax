#include "CDrawDebug.h"
#include "Global.h"

ACDrawDebug::ACDrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	RelativeLocation[0] = FVector(0, 0, 0);
	RelativeLocation[1] = FVector(0, 500, 0);
	RelativeLocation[2] = FVector(-500, 0, 0);
	RelativeLocation[3] = FVector(-1000, 0, 0);

	Box = FBox(FVector(-50, -100, -50), FVector(50, 100, 50));
}

void ACDrawDebug::BeginPlay()
{
	Super::BeginPlay();

	//DrawDebugBox(GetWorld(), GetActorLocation() + Box.GetCenter(), Box.GetExtent(), FColor::Cyan, true);
	
}

void ACDrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < 4; i++)
		WorldLocation[i] = GetActorLocation() + RelativeLocation[i];

	DrawDebugSolidBox(GetWorld(), WorldLocation[0], Box.GetExtent(), FColor::Cyan);
	DrawDebugPoint(GetWorld(), WorldLocation[1], 20, FColor::Red);
	DrawDebugSphere(GetWorld(), WorldLocation[2], 100, 30, FColor::Emerald);
	DrawDebugCircle(GetWorld(), WorldLocation[3], 100, 50, FColor::Blue);

	FVector start = WorldLocation[3];
	FVector end = WorldLocation[1];
	DrawDebugDirectionalArrow(GetWorld(), start, end, 200, FColor::Magenta, false, -1.f, 0, 10.f);
	 
	FVector roundTrip = WorldLocation[2];
	roundTrip.X += sin(GetWorld()->GetTimeSeconds() * 3.f) * 200.f;
	DrawDebugSphere(GetWorld(), roundTrip, 100, 30, FColor::Purple);

}

