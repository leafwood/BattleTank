// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

UENUM()
enum class EFiringStates : uint8
{
	Reloading,
	Firing,
	Reloaded
};

class UTankBarrel;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

	void AimAt(FVector HitLocation);

	void MoveBarrelTowards(FVector AimDirection);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void InitializeAimComp(UTankBarrel* BarrelToSet);

protected:
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStates FiringStates = EFiringStates::Reloaded;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> Projectile_BP;
private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly)
	float CD = 1;

	double Lastfire = 0;
};
