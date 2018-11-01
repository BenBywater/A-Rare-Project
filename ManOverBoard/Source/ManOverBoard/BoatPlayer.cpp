// Fill out your copyright notice in the Description page of Project Settings.

#include "ManOverBoard.h"
#include <math.h>
#include "BoatPlayer.h"


// Sets default values
ABoatPlayer::ABoatPlayer():
	BoatMeshComponent(nullptr),
	WindowMeshComponent(nullptr),
	Camera(nullptr),
	CameraArm(nullptr),
	currentX(0.f),
	currentY(0.f),
	waveAmp1(1),
	waveAmp2(1),
	waveAmp3(1),
	waveFreq1(1.2),
	waveFreq2(1),
	waveFreq3(1.5),
	bobCycle1(0.f),
	bobCycle2(0.f),
	bobCycle3(0.f),
	boatSpeed(500),
	forwardRoll(-3.f),
	reverseRoll(6.f),
	reversePitch(true),
	reverseLock(true),
	pDegree2(-10.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->AutoPossessPlayer = EAutoReceiveInput::Player0;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoatMesh(TEXT("/Game/Boat/Boat"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> windowMesh(TEXT("/Game/StarterContent/Props/SM_GlassWindow"));

	// Create the mesh component
	BoatMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PirateBoat"));
	RootComponent = BoatMeshComponent;
	BoatMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	BoatMeshComponent->SetStaticMesh(BoatMesh.Object);
	BoatMeshComponent->SetRelativeScale3D(FVector(25.f, 30.f, 25.f));
	BoatMeshComponent->SetSimulatePhysics(false);
	BoatMeshComponent->SetEnableGravity(true);
	BoatMeshComponent->SetLinearDamping(0.01);

	WindowMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window"));
	WindowMeshComponent->SetStaticMesh(windowMesh.Object);
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, true);
	WindowMeshComponent->AttachToComponent(BoatMeshComponent, rules, TEXT("Socket"));
	

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

	BobbingBoat(DeltaTime);
	MoveBoat(DeltaTime);
	RotateBoatRoll(DeltaTime);

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


void ABoatPlayer::BobbingBoat(float dTime)
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

void ABoatPlayer::RotateBoatRoll(float dTime)
{
	float degree1 = 100;
	if (reverseLock != false)
	{
		float pitch = dTime * 360;
		pitch /= 2.f;
		forwardRoll += pitch;
		forwardRoll = fmod(forwardRoll, 360);
		degree1 = forwardRoll * 0.01745329251;
		

		if (pDegree2 > degree1)
		{
			pitchList.Pop();
			reverseLock = false;
		}
		else
		{
			FRotator NewRotation = BoatMeshComponent->RelativeRotation;
			NewRotation.Pitch = degree1;

			SetActorRelativeRotation(NewRotation);
			pitchList.Push(degree1);
			pDegree2 = degree1;
		}
		
	}
	else
	{

		FRotator NewRotation = BoatMeshComponent->RelativeRotation;
		NewRotation.Pitch = pitchList.Last();
		SetActorRelativeRotation(NewRotation);
		pitchList.Pop();
		if (pitchList.Num() == 0)
		{
			reverseLock = true;
			pDegree2 = -10.f;
		}
	}
	
	//NewRotation.Roll = degree1;
	//if (reverseLock)
	//{
	//	reversePitch = !reversePitch;
	//	reverseLock = false;
	//	
	//}

	//if (reversePitch)
	//{
	//	float roll = dTime * 360;
	//	roll /= 2.f;
	//	forwardRoll += roll;
	//	forwardRoll = fmod(forwardRoll, 360);
	//	degree2 = forwardRoll * 0.01745329251;
	//	//FVector newRotation = BoatMeshComponent->RelativeRotation.Vector().RotateAngleAxis(degree1, FVector(1, 0, 0));
	//	NewRotation.Pitch = degree2;
	//	SetActorRelativeRotation(NewRotation);
	//	if (degree2 > 6)
	//	{
	//		reverseRoll = 6;
	//		reverseLock = true;
	//	}
	//	UE_LOG(LogTemp, Warning, TEXT("forward Value: %s"), *FString::Printf(TEXT("%f"), degree2));
	//}
	//else
	//{
	//	float roll = dTime * 360;
	//	roll /= 2.f;
	//	reverseRoll -= roll;
	//	reverseRoll = fmod(reverseRoll, 360);
	//	degree2 = reverseRoll * 0.01745329251;
	//	//FVector newRotation = BoatMeshComponent->RelativeRotation.Vector().RotateAngleAxis(degree1, FVector(1, 0, 0));
	//	NewRotation.Pitch = degree2;
	//	SetActorRelativeRotation(NewRotation);
	//	if (degree2 < 1)
	//	{
	//		forwardRoll = 0;
	//		reverseLock = true;
	//	}
	//	UE_LOG(LogTemp, Warning, TEXT("reverse Value: %s"), *FString::Printf(TEXT("%f"), degree2));
	//}
	
	
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