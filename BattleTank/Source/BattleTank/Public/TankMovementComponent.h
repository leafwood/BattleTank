// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankBody;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Speed);

	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Speed);

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBody* BodyToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:

	UTankBody* Body = nullptr;
};
