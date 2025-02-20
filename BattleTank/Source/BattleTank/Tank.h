// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(class UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(class UTankTurret* TurretToSet);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void FireCannons();

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadDelay = 3.f;

	float ReloadTimer = 99999.9f;

	UTankBarrel* Barrel = nullptr;

	
};
