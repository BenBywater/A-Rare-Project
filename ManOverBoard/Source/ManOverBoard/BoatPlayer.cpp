// Fill out your copyright notice in the Description page of Project Settings.

#include "ManOverBoard.h"
#include <math.h>
#include "BoatPlayer.h"


// Sets default values
ABoatPlayer::ABoatPlayer():
	BoatMeshComponent(nullptr),
	Camera(nullptr),
	CameraArm(nullptr),
	currentX(0.f),
	currentY(0.f),
	twoPi(6.28318530718),
	waveAmp1(2.f),
	waveAmp2(1.2),
	waveAmp3(5.f),
	waveFreq1(2.f),
	waveFreq2(10.f),
	waveFreq3(3.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->AutoPossessPlayer = EAutoReceiveInput::Player0;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoatMesh(TEXT("/Game/Boat/Boat"));

	// Create the mesh component
	BoatMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PirateBoat"));
	RootComponent = BoatMeshComponent;
	BoatMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	BoatMeshComponent->SetStaticMesh(BoatMesh.Object);
	BoatMeshComponent->SetRelativeScale3D(FVector(25.f, 30.f, 25.f));
	BoatMeshComponent->SetSimulatePhysics(true);
	BoatMeshComponent->SetEnableGravity(true);
	BoatMeshComponent->SetLinearDamping(0.01);
	

	// Create a camera arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bAbsoluteRotation = false; // Don't want arm to rotate when ship does
	CameraArm->TargetArmLength = 4000.f;
	CameraArm->RelativeRotation = FRotator(-50.f, 90.f, 0.f);
	CameraArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm
	Camera->RelativeRotation = FRotator(-340.f, 0.f, 0.f);
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
	
	RotateBoat(DeltaTime);
	MoveBoat();

}

// Called to bind functionality to input
void ABoatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABoatPlayer::SetXValue(float x)
{
	//UE_LOG(LogTemp, Warning, TEXT("X Value: %s"), *FString::Printf(TEXT("%f"), x))
	currentX = x;
}

void ABoatPlayer::SetYValue(float y)
{
	//UE_LOG(LogTemp, Warning, TEXT("Y Value: %s"), *FString::Printf(TEXT("%f"), y))
	currentY = y;
}

float ABoatPlayer::CalculateSineWaveValue(float x, float amplitude, float frequency)
{

	if (x < 0 || x > 1)
	{
		return 0;
	}
	else
	{
		return amplitude * sin((twoPi * frequency) * x);
	}

}

void ABoatPlayer::RotateBoat(float dTime)
{
	// convert dTime into x
	
	//call sine wave on all three wave setups

	//combine all wave vectors into one to create rotation
}

void ABoatPlayer::MoveBoat()
{

}