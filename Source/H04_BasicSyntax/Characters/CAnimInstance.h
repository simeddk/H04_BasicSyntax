#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class H04_BASICSYNTAX_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerPawn")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerPawn")
		bool bEquipped;

private:
	class ACharacter* OnwerCharacter;
};
