// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"

class UAimingComponent;

UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
public:
	UAimingComponent* AimingComponent=nullptr;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	APawn* Player = nullptr;

private:
	UPROPERTY(EditAnywhere)
	float AcceptanceRatius = 4000;
};
