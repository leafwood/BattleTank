// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBody.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBody : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void LTrack(float LTrackForce);

	UFUNCTION(BlueprintCallable)
	void RTrack(float RTrackForce);

	void AddTrackForce(FVector Location, float TrackForce);

	UPROPERTY(EditDefaultsOnly)
	float MaxForce = 240000.f;
};
