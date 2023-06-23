#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPhysicsCube.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACPhysicsCube : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPhysicsCube();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
};
