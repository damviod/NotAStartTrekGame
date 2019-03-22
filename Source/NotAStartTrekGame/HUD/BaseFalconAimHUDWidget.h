// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BaseFalconAimHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class NOTASTARTTREKGAME_API UBaseFalconAimHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadonly, meta=(BindWidget))
	UTextBlock *TargetDistanceText = nullptr;
	

	
};
