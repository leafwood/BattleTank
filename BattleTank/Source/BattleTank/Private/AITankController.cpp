// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankController.h"
#include "Tank.h"
#include "AimingComponent.h"


void AAITankController::BeginPlay()
{
	Super::BeginPlay();

}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	ControlledTank = Cast<ATank>(GetPawn());
	//TODO Move Towards Player. 

	//Aim At Player.
	FVector HitLocation = Player->GetActorLocation();
	if (ControlledTank && Player)
	{
		MoveToActor(Player, AcceptanceRatius);

		ControlledTank->Aiming(HitLocation);
	}
	//Attack Player.
	ControlledTank->Fire();
}

