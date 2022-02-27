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
	UTankBody();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void LTrack(float LTrackForce);

	UFUNCTION(BlueprintCallable)
	void RTrack(float RTrackForce);

	void AddTrackForce(FVector Location, float TrackForce);

	UPROPERTY(EditDefaultsOnly)
	float MaxForce = 240000.f;
};
