// Fill out your copyright notice in the Description page of Project Settings.

#include "ManOverBoard.h"
#include "BoatPlayer.h"


// Sets default values
ABoatPlayer::ABoatPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoatMesh(TEXT("/Game/Boat/Boat"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/UFO/Blue"));
	// Create the mesh component
	BoatMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PirateBoat"));
	RootComponent = BoatMeshComponent;
	BoatMeshComponent->SetSimulatePhysics(false);
	BoatMeshComponent->SetStaticMesh(BoatMesh.Object);

}

// Called when the game starts or when spawned
void ABoatPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoatPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoatPlayer::SetXValue(float x)
{
	//UE_LOG(LogTemp, Warning, TEXT("X value : %f", *x));
	UE_LOG(LogTemp, Warning, TEXT("X Value: %s"), *FString::Printf(TEXT("%f"), x))
}

void ABoatPlayer::SetYValue(float y)
{
	//UE_LOG(LogTemp, Warning, TEXT("X value : %f", *y));
	UE_LOG(LogTemp, Warning, TEXT("Y Value: %s"), *FString::Printf(TEXT("%f"), y))
}