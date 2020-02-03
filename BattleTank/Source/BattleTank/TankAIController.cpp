// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank) { UE_LOG(LogTemp, Error, TEXT("ControlledTank is null on AI Controller")); return; }
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) { UE_LOG(LogTemp, Error, TEXT("PlayerTank is null on AI Controller")); return; }

}

void ATankAIController::Tick(float DeltaTime)
{
	ControlledTank->AimAt(PlayerTank->GetActorLocation()); // TODO Seems the AI aim is not working

	ControlledTank->FireCannons();
}