#include "CBlueprintEvent.h"
#include "Global.h"
#include "Characters/CPlayer.h"

void ACBlueprintEvent::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBlueprintEvent::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBlueprintEvent::EndOverlap);
}

void ACBlueprintEvent::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	ChangePlayerColor();
}

void ACBlueprintEvent::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	ResetPlayerColor();
}

void ACBlueprintEvent::ResetPlayerColor_Implementation()
{
	FLinearColor originColor = FLinearColor(0.450980f, 0.403922f, 0.360784f);

	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CheckNull(player);

	player->SetColor(originColor, originColor);
}