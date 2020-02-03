// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float MoveSpeed)
{
	MoveSpeed = FMath::Clamp(MoveSpeed, -1.f, 1.f);

	float DeltaPitch = MoveSpeed * ElevationSpeed * GetWorld()->DeltaTimeSeconds;
	float NewPitch = FMath::Clamp(GetRelativeRotation().Pitch + DeltaPitch, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(NewPitch, 0.f, 0.f));

}
