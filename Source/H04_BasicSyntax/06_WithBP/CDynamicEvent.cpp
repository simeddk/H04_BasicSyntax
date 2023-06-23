#include "CDynamicEvent.h"
#include "Global.h"
#include "CVertex.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

ACDynamicEvent::ACDynamicEvent()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACDynamicEvent::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACVertex::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	Vertices[0] = Cast<ACVertex>(actors[0]);
	Vertices[1] = Cast<ACVertex>(actors[1]);

	OnLineTraceResult.AddDynamic(this, &ACDynamicEvent::Ragdoll);
}

void ACDynamicEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Line Start, End
	FVector start = Vertices[0]->GetActorLocation();
	FVector end = Vertices[1]->GetActorLocation();
	
	start.Z -= 20;
	end.Z -= 20;

	//LineTrace
	TArray<AActor*> ignores;
	ignores.Add(Vertices[0]);
	ignores.Add(Vertices[1]);

	FHitResult hitResult;
	if (UKismetSystemLibrary::LineTraceSingleByProfile
	(
		GetWorld(),
		start,
		end,
		"Pawn",
		false,
		ignores,
		EDrawDebugTrace::ForOneFrame,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red
	))
	{
		FLinearColor color = FLinearColor::MakeRandomColor();

		OnLineTraceResult.Broadcast(hitResult.GetActor(), color);
	}

}

void ACDynamicEvent::Ragdoll(AActor* InOhterActor, FLinearColor InColor)
{
	ACharacter* character = Cast<ACharacter>(InOhterActor);
	CheckNull(character);

	character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	character->GetMesh()->SetSimulatePhysics(true);
	character->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	character->GetMesh()->AddImpulse(FVector(1e+5f, 0.f, 0.f));
	character->GetMesh()->GlobalAnimRateScale = 0.f;
}

