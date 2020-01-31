// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}
void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Turret) { return; }
	if (!Barrel) { return; }
	
	FVector HitDirection = HitLocation;
	HitDirection.Normalize();
	RotateTurretTowardsTarget(HitDirection);

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	))
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		RotateBarrelTowardsTarget(AimDirection);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Suggested Projectile Vel is FALSE"), Time);
	}

}

void UTankAimingComponent::RotateBarrelTowardsTarget(FVector TargetDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator TargetRotation = TargetDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);

}

void UTankAimingComponent::RotateTurretTowardsTarget(FVector TargetDirection)
{
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator TargetRotation = TargetDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - TurretRotation;

	Turret->Rotate(DeltaRotation.Yaw);
}



