// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: AI Controller possessing %s"), Time, *ControlledTank->GetName());
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Error, TEXT("%f: AI Controller is not possessing a tank"), Time);
	}
	
	if (GetPlayerTank() != nullptr)
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Player Tank Target Acquired. Kill the motherfucker. His ID is %s"), Time, *GetPlayerTank()->GetName());
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Error, TEXT("%f: AI Controller cannot find player tank"), Time);
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	ATank* TargetTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	GetControlledTank()->AimAt(TargetTank->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{


	return Cast<ATank>(GetPawn());

}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		return Cast<ATank>(PlayerTank);
	}
	
	return nullptr;
}
