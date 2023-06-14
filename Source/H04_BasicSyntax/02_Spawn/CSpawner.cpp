#include "CSpawner.h"
#include "CStaticMesh.h"
#include "CStaticMesh_Cone.h"


ACSpawner::ACSpawner()
{
	CStaticMeshChildOnly = ACStaticMesh_Cone::StaticClass();
}

void ACSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FTransform transform;

	for (int32 i = 0; i < 4; i++)
	{
		SpawnedObjects[i] = GetWorld()->SpawnActor<ACStaticMesh>(ShouldBeSpawn[i], transform);
		
		FVector location = GetActorLocation();
		SpawnedObjects[i]->SetActorLocation(FVector(location.X, location.Y + i * 200, location.Z));
	}

	
}

