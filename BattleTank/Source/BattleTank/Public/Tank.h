// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBody;
class UTankBarrel;
class UAimingComponent;
class AProjectile;
class UCapsuleComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000.f;

	UFUNCTION(BlueprintCallable)
	void InitializeTank(UTankBarrel* BarrelToSet, UAimingComponent* AimingComp);

	void Aiming(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UAimingComponent* AimingComponent = nullptr;

	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> Projectile_BP;
private:

	UPROPERTY(EditDefaultsOnly)
	float CD = 1;

	double Lastfire = 0;
};
