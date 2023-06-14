#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACProperty : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProperty();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		int NumA;

	UPROPERTY(EditDefaultsOnly)
		int NumB;

	UPROPERTY(EditInstanceOnly)
		int NumC;

	UPROPERTY(VisibleAnywhere)
		float RealA = 3.14f;

	UPROPERTY(VisibleDefaultsOnly)
		float RealB = 99.9f;

	UPROPERTY(VisibleInstanceOnly) 
		float RealC = .1f;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FString Message = "Hello World";

};
