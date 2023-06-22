#include "CMulticast.h"
#include "Global.h"
#include "GameFramework/Character.h"

void ACMulticast::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACMulticast::BeginOverlap);
}

void ACMulticast::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	CheckNull(character);

	if (OnMulticast.IsBound())
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);

		FLinearColor color = FLinearColor::MakeRandomColor();
		color.A = 1.f;

		OnMulticast.Broadcast(index, color);
	}
}
