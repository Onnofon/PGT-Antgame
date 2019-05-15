#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Health")
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Health")
		class UUserWidget* CurrentWidget;


};