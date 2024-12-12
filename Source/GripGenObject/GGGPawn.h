// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GGGPawn.generated.h"

UCLASS()
class GRIPGENOBJECT_API AGGGPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGGGPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// 루트 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	// 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	// Motion Controller - 오른손
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* RightController;

	// Motion Controller - 왼손
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* LeftController;

	// OculusXR Hand - 오른손
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UOculusXRHandComponent* RightHand;

	// OculusXR Hand - 왼손
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UOculusXRHandComponent* LeftHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHandJoint* RightHandJoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHandJoint* LeftHandJoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHandTrackingDataComponent* HandTrackingDataComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class ULSTMHandlerComponent* LSTMHandlerComponent;
	
	class UGGGGameInstance* GGGGameInstance;
private:
	TQueue<TArray<float>> JointSequenceData;
public:
	int QueueCount = 0;

	FVector PreRightHandLocation;
	FQuat PreRightHandQuat;
	FVector PreLeftHandLocation;
	FQuat PreLeftHandQuat;

private:
	void PlaceJointOnXRHand();

	void EnqueueJointSequenceData();
};
