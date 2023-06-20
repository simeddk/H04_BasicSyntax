#include "CDelegate.h"
#include "Global.h"
#include "GameFramework/Character.h"

void ACDelegate::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &ACDelegate::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACDelegate::EndOverlap);
}

void ACDelegate::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
	CheckNull(otherCharacter);

	if (OnBoxBeginOverlap.IsBound())
		OnBoxBeginOverlap.Execute();

	if (OnRandomBeginOverlap.IsBound())
	{
		FLinearColor color = FLinearColor::MakeRandomColor();
		color.A = 1.f;

		FString str = OnRandomBeginOverlap.Execute(color);
		CLog::Print(str);
	}
}

void ACDelegate::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
	CheckNull(otherCharacter);

	if (OnBoxEndOverlap.IsBound())
		OnBoxEndOverlap.Execute();
}
