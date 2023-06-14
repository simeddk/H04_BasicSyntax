#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawner.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpawner();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UClass* ClassRef;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACStaticMesh> CStaticMeshChildOnly;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACStaticMesh> ShouldBeSpawn[4];

private:
	class ACStaticMesh* SpawnedObjects[4];
};
