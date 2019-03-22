// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseFalconHUD.h"
#include "Kismet/KismetTextLibrary.h"

void ABaseFalconHUD::SetFalconHUDVisibility_Implementation(bool IsVisible)
{
	if (IsVisible)
		ptrFalconHUDWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	else
		ptrFalconHUDWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void ABaseFalconHUD::BeginPlay()
{
	ptrFalconHUDWidget = CreateWidget<UBaseFalconAimHUDWidget>(GetWorld()->GetFirstPlayerController(), templateFalconHUDWidget);
	ptrFalconHUDWidget->AddToViewport();
	ptrFalconHUDWidget->SetVisibility(ESlateVisibility::Collapsed);

}

void ABaseFalconHUD::SetTargetDistanceText(float distance)
{
	FText distText = UKismetTextLibrary::Conv_FloatToText(distance, ERoundingMode::HalfFromZero, false, false, 7, 7, 0, 0);
	ptrFalconHUDWidget->TargetDistanceText->SetText(distText);
}
