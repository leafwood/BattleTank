// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "AimingComponent.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UAimingComponent>();
	if (AimingComponent)
	{
		FindAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimtowardsCrosshair();
}

void ATankPlayerController::AimtowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }

	FVector OutHitLocation;
	if (GetSightRagHitLocation(OutHitLocation))
	{
		if (GetControlledTank())
		{
			GetControlledTank()->Aiming(OutHitLocation);
		}
	}
}

bool ATankPlayerController::GetSightRagHitLocation(FVector& HitLocation) const
{

	int32 ViewportSizeX,ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	//FVector2D ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);
	FVector WorldLocation,WorldDirection;
	FHitResult Result;
	if (DeprojectScreenPositionToWorld(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY, WorldLocation, WorldDirection))
	{

		GetWorld()->LineTraceSingleByChannel(Result, 
											WorldLocation, 
											WorldLocation + (WorldDirection * 100000.f), 
											ECollisionChannel(ECC_Visibility), 
											FCollisionQueryParams(FName(), 
											false,
											GetWorld()->GetFirstPlayerController()->GetPawn()));

		if (Result.GetActor())
		{
			HitLocation = Result.Location;
		}
	}
	return true;
}

