// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"



UENUM(BlueprintType) // Blueprint에서 사용 가능하도록 선언
enum class EHandType : uint8
{
    RightHand UMETA(DisplayName = "Right Hand"),
    LeftHand UMETA(DisplayName = "Left Hand"),
};

UENUM(BlueprintType) // Blueprint에서 사용 가능하도록 선언
enum class EHandDataLabel : uint8
{
    Idle UMETA(DisplayName = "Idle"),
    Pistol UMETA(DisplayName = "Pistol"),
    Drill UMETA(DisplayName = "Drill"),
    Sword UMETA(DisplayName = "Sword"),
    Dagger UMETA(DisplayName = "Dagger"),
    KitchenKnife UMETA(DisplayName = "KitchenKnife")
};


class UJointMeshComponent;

UCLASS()
class GRIPGENOBJECT_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

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
    class UHandTrackingDataComponent* HandTrackingDataComponent;



protected:
    // StaticMeshComponents for hand joints
    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* WristRoot;

    /*UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UStaticMeshComponent* Forearm_Stub;*/

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Thumb0;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Thumb1;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Thumb2;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Thumb3;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Thumb_Tip;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Index1;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Index2;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Index3;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Index_Tip;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Middle1;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Middle2;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Middle3;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Middle_Tip;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Ring1;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Ring2;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Ring3;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Ring_Tip;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Pinky0;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Pinky1;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Pinky2;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Pinky3;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    UJointMeshComponent* Pinky_Tip;

    //
    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    TArray<UJointMeshComponent*> HandJointMeshes;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    TArray<FVector> HandJointMeshLocations;

    UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
    TArray<FRotator> HandJointMeshRotations;

	
protected:
	//UStaticMeshComponent* CreateBoneStaticMeshComponent(const FString& Name, USceneComponent* Parent);
    void InitializeJointMeshComponent();

    void AppendJointMeshToHandJointMeshes();

	void PlaceJointMeshOnHandJoints();

    void CalculateRelativeJoint();

public:
    UOculusXRHandComponent* GetOculusHand(EHandType _HandType);

    TArray<UJointMeshComponent*> GetHandJointMeshes();
};
