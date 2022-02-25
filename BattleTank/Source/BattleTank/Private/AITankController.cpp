// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankController.h"
#include "Tank.h"
#include "AimingComponent.h"


void AAITankController::BeginPlay()
{
	Super::BeginPlay();

	//ATank* ControlledTank = Cast<ATank>(GetPawn());
	Player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	AimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ensure(Player)) { return; }
	if (!ensure(AimingComponent)) { return; }
	//Aim At Player.
	FVector HitLocation = Player->GetActorLocation();
	if (AimingComponent && Player)
	{
		MoveToActor(Player, AcceptanceRatius);

		AimingComponent->AimAt(HitLocation);
	}
	
	AimingComponent->Fire();
}

