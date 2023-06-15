#include "CGameMode.h"
#include "Characters/CPlayer.h"

ACGameMode::ACGameMode()
{
	//DefaultPawnClass = ACPlayer::StaticClass();
	
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));
	if (pawnAsset.Succeeded())
		DefaultPawnClass = pawnAsset.Class;
}