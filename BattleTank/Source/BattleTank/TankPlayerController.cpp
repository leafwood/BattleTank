// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "AimingComponent.h"
#include "Tank.h"


void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FindAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimtowardsCrosshair();
}

void ATankPlayerController::AimtowardsCrosshair()
{
	if (!ensure(GetPawn())) { return; }
	if (!ensure(AimingComponent)) { return; }
	FVector OutHitLocation;
	if (GetSightRagHitLocation(OutHitLocation))
	{
			AimingComponent->AimAt(OutHitLocation);
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


