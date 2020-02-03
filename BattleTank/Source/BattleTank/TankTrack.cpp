// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float InputValue)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle amount: %f"), *Name, InputValue);

	// TODO Clamp input to max 1??

	FVector Force = GetForwardVector() * InputValue * MaxDrivingForce;
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	FVector ComponentOrigin = GetComponentLocation();
	FVector ForcePointFront = ComponentOrigin + GetForwardVector() * 200;
	FVector ForcePointBack = ComponentOrigin - GetForwardVector() * 200;
	float ForceSplitFactor = 0.5f;
	TankRoot->AddForceAtLocation(Force * ForceSplitFactor, ForcePointFront);
	TankRoot->AddForceAtLocation(Force * ForceSplitFactor, ComponentOrigin);
	TankRoot->AddForceAtLocation(Force * ForceSplitFactor, ForcePointBack);
}
