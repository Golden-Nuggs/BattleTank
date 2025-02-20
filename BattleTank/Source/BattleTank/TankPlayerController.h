// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	float CrossHairAnchorX = 0.5f; 
	UPROPERTY(EditAnywhere)
	float CrossHairAnchorY = 0.33333f;

private:
	class ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector& CameraWorldPosition, FVector& WorldDirection) const;
	bool GetHitInfo(FVector& OutHitLocation, FVector CameraWorldPosition, FVector WorldDirection) const;


};
