// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Player Controller possessing %s"), Time, *ControlledTank->GetName());
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Error, TEXT("%f: Player Controller not possessing a tank"), Time);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	FHitResult Hit;

	if (GetSightRayHitLocation(Hit, HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Sight Ray Hits Nothing!"), Time);
	}


}

bool ATankPlayerController::GetSightRayHitLocation(FHitResult& OutHit, FVector& OutHitLocation) const
{
	FVector CameraWorldPosition;
	FVector WorldDirection;


	GetLookDirection(CameraWorldPosition, WorldDirection);

	if (GetHitInfo(OutHit, OutHitLocation, CameraWorldPosition, WorldDirection))
	{
		return true;
	}
	
	return false;	
}

// Deproject crosshair location into look direction
bool ATankPlayerController::GetLookDirection(FVector& OutCameraWorldPosition, FVector& OutWorldDirection) const
{
	// Find the crosshair position in pixel coords
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrossHairScreenLocation = FVector2D(ViewportSizeX * CrossHairAnchorX, ViewportSizeY * CrossHairAnchorY);


	if (DeprojectScreenPositionToWorld(CrossHairScreenLocation.X, CrossHairScreenLocation.Y, OutCameraWorldPosition, OutWorldDirection))
	{
		return true;
	}
	
	return false;

}

// Line trace along look direction to find location of any hit (visibility channel)
bool ATankPlayerController::GetHitInfo(FHitResult& OutHit, FVector& OutHitLocation, FVector CameraWorldPosition, FVector WorldDirection) const
{
	FHitResult Hit;
	float MaxLengthTrace = 99999.9f;
	FVector LineTraceEnd = CameraWorldPosition + (WorldDirection * MaxLengthTrace);
	if (GetWorld()->LineTraceSingleByChannel(Hit, CameraWorldPosition, LineTraceEnd, ECollisionChannel::ECC_Visibility))
	{
		OutHit = Hit;
		OutHitLocation = Hit.Location;
		return true;
		
	}

	return false;
}

