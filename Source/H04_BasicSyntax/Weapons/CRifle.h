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
	FORCEINLINE bool IsAiming() { return bAiming; }

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Begin_Aim();
	void End_Aim();

	void Begin_Fire();
	void End_Fire();

	UFUNCTION()
		void Firing();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		FName HolsterSocket = "Holster_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		FName HandSocket = "Hand_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		class UAnimMontage* GrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		class UAnimMontage* UngrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
		TSubclassOf<class UCameraShake> CameraShakeClass;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private:
	class ACharacter* OwnerCharacter;
	class AStaticMeshActor* OtherActor;
	
	bool bEquipped;		//OnHand : true, OnHolster : false
	bool bEquipping;	//Is Playing Grap/Ungrap Montage
	bool bAiming;		//Is Mouse Right Button Pressed
	bool bFiring;		//Is Shooting Fire
};
