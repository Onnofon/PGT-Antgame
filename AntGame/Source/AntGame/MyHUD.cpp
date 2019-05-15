#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"


AMyHUD::AMyHUD()
{
	//find location of the object within the content
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarObj(TEXT("/Game/UI/HealthUI"));
	HUDWidgetClass = HealthBarObj.Class;

}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();


}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

