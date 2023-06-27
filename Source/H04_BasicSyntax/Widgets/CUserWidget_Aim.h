#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Aim.generated.h"

UCLASS()
class H04_BASICSYNTAX_API UCUserWidget_Aim : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnTarget();

	UFUNCTION(BlueprintImplementableEvent)
		void OffTarget();
	
};
