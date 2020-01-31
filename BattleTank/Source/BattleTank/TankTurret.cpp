// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float MoveSpeed)
{
	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Rotate Turret Called. Movespeed = %f"), Time, MoveSpeed);

	MoveSpeed = FMath::Clamp(MoveSpeed, -1.f, 1.f);

	float DeltaYaw = MoveSpeed * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	float NewYaw = GetRelativeRotation().Yaw + DeltaYaw;
	SetRelativeRotation(FRotator(0.f, NewYaw, 0.f));
}