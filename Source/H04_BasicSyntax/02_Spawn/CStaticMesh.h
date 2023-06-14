#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMesh.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACStaticMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticMesh();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ChangeColor();

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Mesh;

private:
	class UMaterialInstanceDynamic* DynamicMaterial;
};
