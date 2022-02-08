// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBody.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "AimingComponent.h"
#include "TankMovementComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::InitializeTank(UTankBarrel* BarrelToSet, UAimingComponent* AimingComp)
{
	AimingComponent = AimingComp;
	Barrel = BarrelToSet;
	AimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::Aiming(FVector HitLocation)
{
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(HitLocation,LaunchSpeed);
}

void ATank::Fire()
{
	bool CDExpired = (FPlatformTime::Seconds() - CD > Lastfire);
	if (Barrel && CDExpired)
	{
		auto Bullet = GetWorld()->SpawnActor<AProjectile>(
															Projectile_BP,
															Barrel->GetSocketLocation(FName(TEXT("LaunchPoint"))),
															Barrel->GetSocketRotation(FName(TEXT("LaunchPoint"))));
		Bullet->Launch(LaunchSpeed);
		Lastfire = FPlatformTime::Seconds();
	}

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



