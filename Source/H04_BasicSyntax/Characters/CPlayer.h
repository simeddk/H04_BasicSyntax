#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/IRifle.h"
#include "CPlayer.generated.h"

UCLASS()
class H04_BASICSYNTAX_API ACPlayer : public ACharacter, public IIRifle
{
	GENERATED_BODY()

public:
	ACPlayer();

	FORCEINLINE class ACRifle* GetRifle() override { return Rifle; }
	void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutDirection) override;

	virtual void OnTarget() override;
	virtual void OffTarget() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable)
		void SetColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

	UFUNCTION(BlueprintCallable)
		void SetResetColor();

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void ZoomInFov();

	UFUNCTION(BlueprintImplementableEvent)
		void ZoomOutFov();

private: //Axis Event
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

private: //Action Event
	void OnSprint();
	void OffSprint();

	void OnRifle();

	void OnAim();
	void OffAim();

	void OnFire();
	void OffFire();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private:
	TSubclassOf<class UCUserWidget_Aim> AimWidgetClass;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class ACRifle* Rifle;
	class UCUserWidget_Aim* AimWidget;	
};
