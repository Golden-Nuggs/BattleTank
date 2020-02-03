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
	PrimaryComponentTick.bCanEverTick = false;

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
		//UE_LOG(LogTemp, Warning, TEXT("%f: SuggestProjectileVel returned false. On actor: %s"), Time, *GetOwner()->GetName());
	}

}

void UTankAimingComponent::RotateBarrelTowardsTarget(FVector TargetDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator TargetRotation = TargetDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	if (FMath::Abs<float>(DeltaRotation.Yaw) <= 180.f)
	{
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotation.Yaw);
	}
}




