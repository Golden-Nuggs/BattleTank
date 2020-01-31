// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

private:
	class UTankBarrel* Barrel = nullptr;
	class UTankTurret* Turret = nullptr;

	void RotateBarrelTowardsTarget(FVector TargetDirection);
	void RotateTurretTowardsTarget(FVector TargetDirection);
public:
	void SetBarrelReference(class UTankBarrel* BarrelToSet);
	void SetTurretReference(class UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);


};
