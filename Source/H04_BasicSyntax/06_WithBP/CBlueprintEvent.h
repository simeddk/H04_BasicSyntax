#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CBlueprintEvent.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACBlueprintEvent : public ACBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent) //BI
		void ChangePlayerColor();

	UFUNCTION(BlueprintNativeEvent) //BN
		void ResetPlayerColor();

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
