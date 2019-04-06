// Fill out your copyright notice in the Description page of Project Settings.

#include "FalconCameraShake.h"



UFalconCameraShake::UFalconCameraShake()
{
	OscillationDuration = 1.f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.5;
	RotOscillation.Roll.Amplitude = 10.f;
	RotOscillation.Roll.Frequency = 5.f;

	LocOscillation.X.Amplitude = 30.f;
	LocOscillation.X.Frequency = 30.f;
	LocOscillation.Y.Amplitude = 30.f;
	LocOscillation.Y.Frequency = 30.f;
	LocOscillation.Z.Amplitude = 30.f;
	LocOscillation.Z.Frequency = 30.f;
}
