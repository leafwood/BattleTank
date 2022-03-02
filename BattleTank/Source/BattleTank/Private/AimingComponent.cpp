// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	Lastfire = FPlatformTime::Seconds();
}

EFiringStates UAimingComponent::GetFiringState() const
{
	return FiringStates;
}

void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (FiringStates == EFiringStates::OutAmmo) { return; }
	auto BarrelDerection = Barrel->GetForwardVector();
	if (FPlatformTime::Seconds() - CD > Lastfire)
	{
		FiringStates = EFiringStates::Reloaded;
		if (!BarrelDerection.Equals(AimDirection, 0.1))
		{
			FiringStates = EFiringStates::Aiming;
		}
	}
	else
	{
		FiringStates = EFiringStates::Reloading;
	}
}

void UAimingComponent::InitializeAimComp(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
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

	AimDirection = OutLaunchVelocity.GetSafeNormal();
	if (Aiming)
	{
		MoveBarrelTowards(AimDirection);
	}
}

void UAimingComponent::MoveBarrelTowards(FVector AimingDirection)
{
	if (!ensure(Barrel)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimingDirection.Rotation();
	auto DletaRotator = AimRotator - BarrelRotator;
	if (DletaRotator.Yaw > 180.f || DletaRotator.Yaw < -180.f)
	{
		DletaRotator.Yaw = -(DletaRotator.Yaw - 180.f);
	}
	Barrel->Aim(DletaRotator.Pitch, DletaRotator.Yaw);
}

void UAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if (FiringStates == EFiringStates::OutAmmo) { return; }
	if (FiringStates != EFiringStates::Reloading)
	{
		auto Bullet = GetWorld()->SpawnActor<AProjectile>(
			Projectile_BP,
			Barrel->GetSocketLocation(FName(TEXT("LaunchPoint"))),
			Barrel->GetSocketRotation(FName(TEXT("LaunchPoint"))));
		if (!ensure(Bullet)) { return; }
		Bullet->Launch(LaunchSpeed);
		Lastfire = FPlatformTime::Seconds();
		AmmoNum -= 1;
		if (AmmoNum == 0) { FiringStates = EFiringStates::OutAmmo; }
	}
}



