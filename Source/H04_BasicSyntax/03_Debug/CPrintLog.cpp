#include "CPrintLog.h"
#include "Global.h"

ACPrintLog::ACPrintLog()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPrintLog::BeginPlay()
{
	Super::BeginPlay();
	
	CLog::Print(1);
	CLog::Print(2, 1);
	CLog::Print(3, 2);
	CLog::Print(4, 2);
	CLog::Print(99.9f, 3, 20, FColor::Green);
	CLog::Print("Hello");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

	CLog::Log(20);
	CLog::Log(PI);
	CLog::Log("Log Test");
	CLog::Log(FVector(100, 200, 300));
	CLog::Log(FRotator(90, 0, 0));
	CLog::Log(someActor);
	CLog::Log(this);
	CLog::Log(__FILE__);
	PrintLine();

	if (false)
		PrintLine();
}

void ACPrintLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	CLog::Print(RunningTime, 10);

	CLog::Print(GetWorld()->TimeSeconds, 11, DeltaTime, FColor::Red);

	//CLog::Print(someActor->GetName());
}

