// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float MoveSpeed);

private:
	UPROPERTY(EditDefaultsOnly)
	float ElevationSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MinElevation = 0;

	UPROPERTY(EditDefaultsOnly)
	float MaxElevation = 40;

};
