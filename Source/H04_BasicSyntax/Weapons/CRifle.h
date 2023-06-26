#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRifle.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRifle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	static ACRifle* Spawn(UWorld* InWorld, ACharacter* InOwner);

	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		FName HolsterSocket = "Holster_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		FName HandSocket = "Hand_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		class UAnimMontage* GrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		class UAnimMontage* UngrabMontage;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private:
	class ACharacter* OwnerCharacter;
	
	bool bEquipped; //OnHand : true, OnHolster : false
	bool bEquipping; //Is Playing Grap/Ungrap Montage
};
