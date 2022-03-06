// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankBody.h"

void UTankMovementComponent::IntendMoveForward(float Speed)
{
	if (!ensure(Body)) { return; }
	Body->LTrack(Speed);
	Body->RTrack(Speed);
}

void UTankMovementComponent::IntendTurnRight(float Speed)
{
	if (!ensure(Body)) { return; }
	Body->LTrack(Speed*1.4);
	Body->RTrack(-Speed*1.4);
}

void UTankMovementComponent::Initialize(UTankBody* BodyToSet)
{
	Body = BodyToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto FaceVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AlIntendVector = MoveVelocity.GetSafeNormal();

	auto Cosine = FVector::DotProduct(FaceVector, AlIntendVector);
	auto Sine = FVector::CrossProduct(FaceVector, AlIntendVector);

	IntendMoveForward(2 * Cosine);
	IntendTurnRight(2 * Sine.Z);
}
