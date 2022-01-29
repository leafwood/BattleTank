// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBody.h"

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
	//auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	AddForceAtLocation(DirectionForce, Location);
}