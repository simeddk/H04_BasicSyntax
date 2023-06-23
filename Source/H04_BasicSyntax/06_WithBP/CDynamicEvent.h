#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDynamicEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceResult, AActor*, InOhterActor, FLinearColor, InColor);

UCLASS()
class H04_BASICSYNTAX_API ACDynamicEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDynamicEvent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void Ragdoll(AActor* InOhterActor, FLinearColor InColor);

private:
	class ACVertex* Vertices[2];

public:
	UPROPERTY(BlueprintAssignable)
		FLineTraceResult OnLineTraceResult;
};
