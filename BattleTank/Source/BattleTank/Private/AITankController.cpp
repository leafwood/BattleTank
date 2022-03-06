// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankController.h"
#include "AimingComponent.h"
#include "Tank.h"

void AAITankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AAITankController::OnPossessedTankDeath);
	}
}

void AAITankController::OnPossessedTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}

void AAITankController::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();

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

	if (AimingComponent->GetFiringState() == EFiringStates::Reloaded)
	{
		AimingComponent->Fire();
	}
}

