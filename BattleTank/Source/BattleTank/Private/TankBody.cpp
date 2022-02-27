// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBody.h"

UTankBody::UTankBody()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankBody::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //rightvector is the y unit vector in the world space,dotproduct  just means componentvelocity partially in y.
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    auto CorrectionVector = -SlippageSpeed / DeltaTime * GetRightVector();
    auto RootComp = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = RootComp->GetMass() * CorrectionVector;
    RootComp->AddForce(CorrectionForce);
}


void UTankBody::LTrack(float LTrackForce)
{
	AddTrackForce(GetSocketLocation("LeftTrack"), LTrackForce);
}

void UTankBody::RTrack(float RTrackForce)
{
	AddTrackForce(GetSocketLocation("RightTrack"), RTrackForce);
}

void UTankBody::AddTrackForce(FVector Location, float TrackForce)
{
	auto DirectionForce = GetForwardVector() * TrackForce * MaxForce;
	AddForceAtLocation(DirectionForce, Location);
}