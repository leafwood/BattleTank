// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FindAimingComponent(UAimingComponent* AimingComp);

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UAimingComponent* AimingComponent = nullptr;

	ATank* ControlledTank = nullptr;
private:
	void AimtowardsCrosshair();

	bool GetSightRagHitLocation(FVector&) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3f;
};
