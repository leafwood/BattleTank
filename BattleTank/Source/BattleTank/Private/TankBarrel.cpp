// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Aim(float RelativePitchSpeed, float RelativeYawSpeed)
{

	auto NewRelativePitchSpeed = FMath::Clamp<float>(RelativePitchSpeed, -1.f, 1.f);
	auto NewRelativeYawSpeed = FMath::Clamp<float>(RelativeYawSpeed, -1.f, 1.f);

	auto ElevationChange = NewRelativePitchSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RotationChange = NewRelativeYawSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewElevation = ElevationChange + GetRelativeRotation().Pitch;
	auto RawNewRotation = RotationChange + GetRelativeRotation().Yaw;

	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinDegree, MaxDegree), RawNewRotation, 0));
}

