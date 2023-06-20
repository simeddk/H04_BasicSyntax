#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CComponentOverlap.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACComponentOverlap : public ACBox
{
	GENERATED_BODY()

public:
	ACComponentOverlap();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight;
};
