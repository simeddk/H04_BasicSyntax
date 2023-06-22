#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CEvent.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACEvent : public ACBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	DECLARE_EVENT_OneParam(ACEvent, FEventSignature, int32);

	FEventSignature OnEvent;

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
