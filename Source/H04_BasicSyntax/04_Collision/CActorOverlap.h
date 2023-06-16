#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CActorOverlap.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACActorOverlap : public ACBox
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
