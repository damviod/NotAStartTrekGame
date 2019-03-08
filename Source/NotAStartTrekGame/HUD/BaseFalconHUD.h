// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "BaseFalconHUD.generated.h"

/**
 * 
 */
UCLASS()
class NOTASTARTTREKGAME_API ABaseFalconHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="Falcon Huds")
	TSubclassOf<UUserWidget> templateFalconHUDWidget;
	
	UFUNCTION(BlueprintImplementableEvent, Category="Falcon Huds")
	void SetFalconHUDVisibility(bool IsVisible);
	
};
