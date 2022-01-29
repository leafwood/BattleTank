// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "TankBarrel.h"
#include "Tank.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector LaunchPoint = Barrel->GetSocketLocation(FName("LaunchPoint"));
	//Draw Projectile Line.
	bool Aiming = UGameplayStatics::SuggestProjectileVelocity(
						this, 
						OutLaunchVelocity, 
						LaunchPoint, 
						HitLocation, 
						LaunchSpeed, 
						false, 
						0, 
						0, 
						ESuggestProjVelocityTraceOption::DoNotTrace);

	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	if (Aiming)
	{
		MoveBarrelTowards(AimDirection);
	}
}

void UAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DletaRotator = AimRotator - BarrelRotator;

	Barrel->Aim(DletaRotator.Pitch, DletaRotator.Yaw);
}



