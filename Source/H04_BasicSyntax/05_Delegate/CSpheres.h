#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpheres.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACSpheres : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpheres();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void Falling(int32 InIndex, FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Spheres[3];

private:
	FVector OriginLocation[3];
	class UMaterialInstanceDynamic* DynamicMaterials[3];
};
