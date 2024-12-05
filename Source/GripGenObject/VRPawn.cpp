// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "OculusXRHandComponent.h"
#include "OculusXRInputFunctionLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"

#include "HandTrackingDataComponent.h"
#include "LSTMHandlerComponent.h"
#include "JointMeshComponent.h"

#include "Engine/AssetManager.h"


// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 루트 컴포넌트 생성
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = Root;

    // 카메라 컴포넌트 생성 및 부착
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(Root);

    // 초기 위치 설정 (필요 시)
    //CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f)); // 예: Pawn의 머리 높이
    //CameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); // 약간 아래로 향하도록 설정

    // 오른손 Motion Controller 생성
    RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
    RightController->SetupAttachment(Root);
    RightController->SetTrackingSource(EControllerHand::Right); // 오른손 설정

    // 왼손 Motion Controller 생성
    LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
    LeftController->SetupAttachment(Root);
    LeftController->SetTrackingSource(EControllerHand::Left); // 왼손 설정

    // 오른손 OculusXR Hand 컴포넌트 생성
    RightHand = CreateDefaultSubobject<UOculusXRHandComponent>(TEXT("RightHand"));
    RightHand->SetupAttachment(RightController);
    RightHand->SkeletonType = EOculusXRHandType::HandRight;
    
    // 왼손 OculusXR Hand 컴포넌트 생성
    LeftHand = CreateDefaultSubobject<UOculusXRHandComponent>(TEXT("LeftHand"));
    LeftHand->SetupAttachment(LeftController);
    LeftHand->SkeletonType = EOculusXRHandType::HandLeft;

    // HandTrackingDataComponent
    HandTrackingDataComponent = CreateDefaultSubobject<UHandTrackingDataComponent>(TEXT("HandTrackingDataComponent"));
    
    // LSTMHandlerComponent
    LSTMHandlerComponent = CreateDefaultSubobject<ULSTMHandlerComponent>(TEXT("LSTMHandlerComponent"));

    InitializeJointMeshComponent();

    AppendJointMeshToHandJointMeshes();

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
   
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    PlaceJointMeshOnHandJoints();
    //CalculateRelativeJoint();
}



// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVRPawn::InitializeJointMeshComponent()
{
    // StaticMeshComponents 생성 및 부착
    WristRoot = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Wrist Root"));
    WristRoot->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::WristRoot);

    Thumb0 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb0"));
    Thumb0->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Thumb0);

    Thumb1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb1"));
    Thumb1->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Thumb1);

    Thumb2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb2"));
    Thumb2->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Thumb2);

    Thumb3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb3"));
    Thumb3->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Thumb3);

    Thumb_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb Tip"));
    Thumb_Tip->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Thumb_Tip);

    Index1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Index1"));
    Index1->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Index1);

    Index2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Index2"));
    Index2->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Index2);

    Index3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Index3"));
    Index3->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Index3);

    Index_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Index Tip"));
    Index_Tip->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Index_Tip);

    Middle1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Middle1"));
    Middle1->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Middle1);

    Middle2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Middle2"));
    Middle2->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Middle2);

    Middle3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Middle3"));
    Middle3->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Middle3);

    Middle_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Middle Tip"));
    Middle_Tip->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Middle_Tip);

    Ring1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Ring1"));
    Ring1->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Ring1);

    Ring2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Ring2"));
    Ring2->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Ring2);

    Ring3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Ring3"));
    Ring3->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Ring3);

    Ring_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Ring Tip"));
    Ring_Tip->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Ring_Tip);

    Pinky0 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky0"));
    Pinky0->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Pinky0);

    Pinky1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky1"));
    Pinky1->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Pinky1);

    Pinky2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky2"));
    Pinky2->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Pinky2);

    Pinky3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky3"));
    Pinky3->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Pinky3);

    Pinky_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky Tip"));
    Pinky_Tip->SetupAttachment(RightHand);
    WristRoot->SetHandJointType(EHandJoint::Pinky_Tip);
}

void AVRPawn::AppendJointMeshToHandJointMeshes()
{
    HandJointMeshes.Add(WristRoot);
    //HandJointMeshes.Add(FName("Forearm_Stub"), Forearm_Stub);

    HandJointMeshes.Add(Thumb0);
    HandJointMeshes.Add(Thumb1);
    HandJointMeshes.Add(Thumb2);
    HandJointMeshes.Add(Thumb3);
    HandJointMeshes.Add(Thumb_Tip);

    HandJointMeshes.Add(Index1);
    HandJointMeshes.Add(Index2);
    HandJointMeshes.Add(Index3);
    HandJointMeshes.Add(Index_Tip);

    HandJointMeshes.Add(Middle1);
    HandJointMeshes.Add(Middle2);
    HandJointMeshes.Add(Middle3);
    HandJointMeshes.Add(Middle_Tip);

    HandJointMeshes.Add(Ring1);
    HandJointMeshes.Add(Ring2);
    HandJointMeshes.Add(Ring3);
    HandJointMeshes.Add(Ring_Tip);

    HandJointMeshes.Add(Pinky0);
    HandJointMeshes.Add(Pinky1);
    HandJointMeshes.Add(Pinky2);
    HandJointMeshes.Add(Pinky3);
    HandJointMeshes.Add(Pinky_Tip);
}

void AVRPawn::PlaceJointMeshOnHandJoints()
{
    for (auto& HandJoint : HandJointMeshes)
    {
        if (RightHand)
        {
            //UE_LOG(LogTemp, Warning, TEXT("Righthand NOt NULL"));
        }
        //RightHand->GetBoneLocation
        //FVector JointLocation = RightHand->GetBoneLocationByName(HandJoint->GetFName(), EBoneSpaces::WorldSpace);
        FRotator JointRotation = RightHand->GetBoneRotationByName(HandJoint->GetFName(), EBoneSpaces::WorldSpace);
        FVector JointLocation = RightHand->GetBoneLocation(HandJoint->GetFName(), EBoneSpaces::WorldSpace);
        //FRotator JointRotation = RightHand->GetBoneRota(HandJoint->GetFName(), EBoneSpaces::WorldSpace);
        HandJoint->SetWorldLocation(JointLocation);
        HandJoint->SetWorldRotation(JointRotation);

        //UE_LOG(LogTemp, Display, TEXT("%s :  %f   %f   %f   %f   %f   %f"), *HandJoint->GetFName().ToString(), JointLocation.X, JointLocation.Y, JointLocation.Z, JointRotation.Pitch, JointRotation.Yaw, JointRotation.Roll);
        //UE_LOG(LogTemp, Display, TEXT("%s"), *HandJoint->GetName());
    }
}

//void AVRPawn::CalculateRelativeJoint()
//{
//    HandJointRelativeLocations.Empty();
//    HandJointRelativeRotations.Empty();
//
//    // StartIndex = NextIndex of RootWrist
//    for (int i = 1; i< HandJointMeshes.Num(); i++)
//    {
//        if (i == 1 || i == 6 || i == 10 || i == 14 || i == 18)
//        {
//            FVector ParentJointLocation = HandJointMeshes[0]->GetComponentLocation();
//            FVector ChildJointLocation = HandJointMeshes[i]->GetComponentLocation();
//            HandJointRelativeLocations.Add(ChildJointLocation - ParentJointLocation);
//
//            FQuat ParentJointQuat = HandJointMeshes[0]->GetComponentQuat();
//            FQuat ChildJointQuat = HandJointMeshes[i]->GetComponentQuat();
//
//            FQuat RelativeQuat = ChildJointQuat * ParentJointQuat.Inverse();
//            FRotator RelativeRotation = RelativeQuat.Rotator();
//            HandJointRelativeRotations.Add(RelativeRotation);
//
//            DrawDebugLine(GetWorld(), ParentJointLocation, ChildJointLocation, FColor::Green, false, -1.0f);
//        }
//        else
//        {
//            FVector ParentJointLocation = HandJointMeshes[i-1]->GetComponentLocation();
//            FVector ChildJointLocation = HandJointMeshes[i]->GetComponentLocation();
//            HandJointRelativeLocations.Add(ChildJointLocation - ParentJointLocation);
//
//            FQuat ParentJointQuat = HandJointMeshes[i-1]->GetComponentQuat();
//            FQuat ChildJointQuat = HandJointMeshes[i]->GetComponentQuat();
//
//            FQuat RelativeQuat = ChildJointQuat * ParentJointQuat.Inverse();
//            FRotator RelativeRotation = RelativeQuat.Rotator();
//            HandJointRelativeRotations.Add(RelativeRotation);
//
//            DrawDebugLine(GetWorld(), ParentJointLocation, ChildJointLocation, FColor::Green, false, -1.0f);
//        }
//    }
//}


UOculusXRHandComponent* AVRPawn::GetOculusHand(EHandType _HandType)
{
    if (_HandType == EHandType::LeftHand)
    {
        return LeftHand;
    }
    else if (_HandType == EHandType::RightHand)
    {
        return RightHand;
    }

    return nullptr;
}

const TArray<UJointMeshComponent*>& AVRPawn::GetHandJointMeshes()
{
    return HandJointMeshes;
}

