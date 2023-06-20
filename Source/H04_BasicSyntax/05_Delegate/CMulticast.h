#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CMulticast.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastSignatrue, int32, FLinearColor); //void(int32, FLinearColor)

UCLASS()
class H04_BASICSYNTAX_API ACMulticast : public ACBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FMulticastSignatrue OnMulticast;
};
