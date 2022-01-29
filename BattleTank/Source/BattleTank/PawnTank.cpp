// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(MoveSpeed * Value * GetWorld()->DeltaTimeSeconds,0,0);
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmount = (RotateSpeed * Value * GetWorld()->DeltaTimeSeconds);
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
	AddActorLocalRotation(RotationDirection, true);
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);

}