#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Repeat.generated.h"

UCLASS()
class H04_BASICSYNTAX_API UCUserWidget_Repeat : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnRepeat();

	UFUNCTION(BlueprintImplementableEvent)
		void OffRepeat();
	
};
