// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Aim(float RelativePitchSpeed, float RelativeYawSpeed)
{
	//get Delta Angle Clamped between 1.0 and -1.0.
	auto NewRelativePitchSpeed = FMath::Clamp<float>(RelativePitchSpeed, -1.f, 1.f);
	auto NewRelativeYawSpeed = FMath::Clamp<float>(RelativeYawSpeed, -1.f, 1.f);
	//extra step to make out framerate issues.
	auto ElevationChange = NewRelativePitchSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RotationChange = NewRelativeYawSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	//Delta Angle Clamped between 1.0 and -1.0 being Added to present Angle
	auto RawNewElevation = ElevationChange + GetRelativeRotation().Pitch;
	auto RawNewRotation = RotationChange + GetRelativeRotation().Yaw;
	//set barrel to the new rotation in a certain speed until no offset exists.
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinDegree, MaxDegree), RawNewRotation, 0));	
}

