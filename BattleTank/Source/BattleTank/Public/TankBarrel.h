// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Aim(float RelativePitchSpeed, float RelativeYawSpeed);


private:
	UPROPERTY(EditAnywhere)
		float MaxDegreePerSecond = 50.f;
	UPROPERTY(EditAnywhere)
		float MaxDegree = 40.f;
	UPROPERTY(EditAnywhere)
		float MinDegree = 0.f;
};
