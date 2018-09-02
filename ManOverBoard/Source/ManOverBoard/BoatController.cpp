// Fill out your copyright notice in the Description page of Project Settings.

#include "ManOverBoard.h"
#include "BoatPlayer.h"
#include "BoatController.h"


ABoatController::ABoatController():
	boatPawn(nullptr),
	inputX(0.f),
	inputY(0.f)
{
	
}

void ABoatController::BeginPlay()
{
	Super::BeginPlay();

	// Spawn Boat
	FVector location = FVector(70.f, -9450.f, 620.f);
	FRotator rotate = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnInfo;
	boatPawn = GetWorld()->SpawnActor<ABoatPlayer>(ABoatPlayer::StaticClass(), location, rotate, SpawnInfo);
}


void ABoatController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// Drive Boat

}

void ABoatController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("XAxisMovementBoat", this, &ABoatController::PassXValue);
	InputComponent->BindAxis("YAxisMovementBoat", this, &ABoatController::PassYValue);
	
}

void ABoatController::PassXValue(float x)
{
	if (boatPawn != nullptr)
	{
		boatPawn->SetXValue(x);
	}
}

void ABoatController::PassYValue(float y)
{
	if (boatPawn != nullptr)
	{
		boatPawn->SetYValue(y);
	}
}