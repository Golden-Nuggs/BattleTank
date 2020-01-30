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
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller is not possessing a tank"));
	}
	
	if (GetPlayerTank() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Target Acquired. Kill the motherfucker. His ID is %s"), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller cannot find player tank"));
	}

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
