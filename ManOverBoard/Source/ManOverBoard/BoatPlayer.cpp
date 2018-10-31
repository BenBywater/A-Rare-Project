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
	waveAmp1(1),
	waveAmp2(1),
	waveAmp3(1),
	waveFreq1(2),
	waveFreq2(1),
	waveFreq3(1.5),
	bobCycle1(0.f),
	bobCycle2(0.f),
	bobCycle3(0.f),
	boatSpeed(500)
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
	BoatMeshComponent->SetSimulatePhysics(false);
	BoatMeshComponent->SetEnableGravity(true);
	BoatMeshComponent->SetLinearDamping(0.01);
	

	// Create a camera arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bAbsoluteRotation = false; // Don't want arm to rotate when ship does
	CameraArm->TargetArmLength = 4000.f;
	CameraArm->RelativeRotation = FRotator(-40.f, 90.f, 0.f);
	CameraArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm
	

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
	MoveBoat(DeltaTime);

}

// Called to bind functionality to input
void ABoatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABoatPlayer::SetXValue(float x)
{
	UE_LOG(LogTemp, Warning, TEXT("X Value: %s"), *FString::Printf(TEXT("%f"), x))
	currentX = x;
}

void ABoatPlayer::SetYValue(float y)
{
	UE_LOG(LogTemp, Warning, TEXT("Y Value: %s"), *FString::Printf(TEXT("%f"), y))
	currentY = y;
}


void ABoatPlayer::RotateBoat(float dTime)
{
	// convert dTime into x
	float xWave1 = dTime * 360;
	xWave1 /= waveFreq1;
	bobCycle1 += xWave1;
	bobCycle1 = fmod(bobCycle1, 360);
	float degree1 = bobCycle1 * 0.01745329251;
	float bobCycle1Sine = sin(degree1) * waveAmp1;
	
	float xWave2 = dTime * 360;
	xWave2 /= waveFreq2;
	bobCycle2 += xWave2;
	bobCycle2 = fmod(bobCycle2, 360);
	float degree2 = bobCycle2 * 0.01745329251;
	float bobCycle2Sine = sin(degree2) * waveAmp2;

	float xWave3 = dTime * 360;
	xWave3 /= waveFreq3;
	bobCycle3 += xWave3;
	bobCycle3 = fmod(bobCycle3, 360);
	float degree3 = bobCycle3 * 0.01745329251;
	float bobCycle3Sine = sin(degree3) * waveAmp3;
	
	//combine all wave vectors into one to create rotation
	FVector loc = BoatMeshComponent->RelativeLocation;
	FVector newLoc = loc;
	float zPlane = bobCycle1Sine + bobCycle2Sine + bobCycle3Sine;

	newLoc.Z += zPlane;
	BoatMeshComponent->SetRelativeLocation(newLoc);
}

void ABoatPlayer::MoveBoat(float dTime)
{
	FRotator NewRotation = BoatMeshComponent->RelativeRotation;
	if (currentY > 0)
	{
		FVector cameraForward = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector();

		cameraForward.Z = 0.0f;
		cameraForward.Normalize();

		// calculate rotation
		if (currentY != 0)
		{
			if (currentX < 0)
			{
				if (NewRotation.Pitch > -10)
				{
					NewRotation.Pitch += -0.1;
				}
				NewRotation.Yaw += -0.2;
			}
			else if (currentX > 0)
			{
				if (NewRotation.Pitch < 10)
				{
					NewRotation.Pitch += 0.1;

				}
				NewRotation.Yaw += 0.2;
			}
			else if (currentX == 0)
			{
				if (NewRotation.Pitch > 0)
				{
					NewRotation.Pitch += -0.1;
				}

				if (NewRotation.Pitch < 0)
				{
					NewRotation.Pitch += 0.1;
				}
			}
		}


		FVector MoveDirection = CameraArm->GetForwardVector() * 1.5;


		MoveDirection.Z = 0;
		// Calculate movement based on direction, speed of player and frame rate dependancy
		const FVector Movement = MoveDirection * boatSpeed * dTime;

		FHitResult Hit(1.f);
		//// move player boat
		BoatMeshComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			BoatMeshComponent->MoveComponent(Deflection, NewRotation, true);
		}
	
	}
	else
	{
			if (NewRotation.Pitch > 0)
			{
				NewRotation.Pitch += -0.05;
			}

			if (NewRotation.Pitch < 0)
			{
				NewRotation.Pitch += 0.05;
			}

		SetActorRelativeRotation(NewRotation);
	}
}