#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertex.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACVertex : public AActor
{
	GENERATED_BODY()
	
public:	
	ACVertex();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
};
