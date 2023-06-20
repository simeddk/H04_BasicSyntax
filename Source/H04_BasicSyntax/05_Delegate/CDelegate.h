#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CDelegate.generated.h"

DECLARE_DELEGATE(FBoxBeginOverlapSignature); // void()
DECLARE_DELEGATE(FBoxEndOverlapSignature); // void()
DECLARE_DELEGATE_RetVal_OneParam(FString, FRandomBeginOverlapSignature, FLinearColor); //FString(FLinearColor)

UCLASS()
class H04_BASICSYNTAX_API ACDelegate : public ACBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FBoxBeginOverlapSignature OnBoxBeginOverlap;
	FBoxEndOverlapSignature OnBoxEndOverlap;
	FRandomBeginOverlapSignature OnRandomBeginOverlap;
};
