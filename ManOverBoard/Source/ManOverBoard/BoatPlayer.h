// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BoatPlayer.generated.h"


UCLASS()
class MANOVERBOARD_API ABoatPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoatPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetXValue(float x);

	void SetYValue(float y);

	void MoveBoat(float dTime);
	void BobbingBoat(float dTime);
	void RotateBoatRoll(float dTime);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UStaticMeshComponent* BoatMeshComponent;
	UStaticMeshComponent* WindowMeshComponent;

	UCameraComponent* Camera;

	USpringArmComponent* CameraArm;

	float currentX;
	float currentY;

	float waveAmp1;
	float waveAmp2;
	float waveAmp3;

	float waveFreq1;
	float waveFreq2;
	float waveFreq3;

	float bobCycle1;
	float bobCycle2;
	float bobCycle3;

	float reverseRoll;
	float forwardRoll;
	bool reversePitch;
	bool reverseLock;
	float pDegree2;
	TArray<float> pitchList;

	float boatSpeed;

	
};
