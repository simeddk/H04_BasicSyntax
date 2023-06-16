#include "CBox.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACBox::ACBox()
{
	//Create Scene Component
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Box, "Box", Root);
	CHelpers::CreateSceneComponent(this, &Text, "Text", Root);
	
	//Components Settings
	Box->bHiddenInGame = false;
	Box->SetRelativeScale3D(FVector(3.f));

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->TextRenderColor = FColor::Black;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());
}

void ACBox::BeginPlay()
{
	Super::BeginPlay();
	
}

