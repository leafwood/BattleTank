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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

	void AimAt(FVector HitLocation,float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void MoveBarrelTowards(FVector AimDirection);

protected:
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStates FiringStates = EFiringStates::Reloaded;
private:

};
