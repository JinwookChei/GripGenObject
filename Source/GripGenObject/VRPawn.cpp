// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "OculusXRHandComponent.h"
#include "OculusXRInputFunctionLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"


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


    InitializeJointMeshComponent();

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

    AppendJointMeshToHandJointMeshes();
 

}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    PlaceJointMeshOnHandJoints();
}



// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVRPawn::InitializeJointMeshComponent()
{
    // StaticMeshComponents 생성 및 부착
    WristRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wrist Root"));
    WristRoot->SetupAttachment(RightHand);

    //Forearm_Stub = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forearm_Stub"));
    //Forearm_Stub->SetupAttachment(RightHand);

    Thumb0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thumb0"));
    Thumb0->SetupAttachment(RightHand);

    Thumb1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thumb1"));
    Thumb1->SetupAttachment(RightHand);

    Thumb2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thumb2"));
    Thumb2->SetupAttachment(RightHand);

    Thumb3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thumb3"));
    Thumb3->SetupAttachment(RightHand);

    Index1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Index1"));
    Index1->SetupAttachment(RightHand);

    Index2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Index2"));
    Index2->SetupAttachment(RightHand);

    Index3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Index3"));
    Index3->SetupAttachment(RightHand);

    Middle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle1"));
    Middle1->SetupAttachment(RightHand);

    Middle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle2"));
    Middle2->SetupAttachment(RightHand);

    Middle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle3"));
    Middle3->SetupAttachment(RightHand);

    Ring1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring1"));
    Ring1->SetupAttachment(RightHand);

    Ring2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring2"));
    Ring2->SetupAttachment(RightHand);

    Ring3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring3"));
    Ring3->SetupAttachment(RightHand);

    Pinky0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pinky0"));
    Pinky0->SetupAttachment(RightHand);

    Pinky1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pinky1"));
    Pinky1->SetupAttachment(RightHand);

    Pinky2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pinky2"));
    Pinky2->SetupAttachment(RightHand);

    Pinky3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pinky3"));
    Pinky3->SetupAttachment(RightHand);

    Thumb_Tip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thumb Tip"));
    Thumb_Tip->SetupAttachment(RightHand);

    Index_Tip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Index Tip"));
    Index_Tip->SetupAttachment(RightHand);

    Middle_Tip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle Tip"));
    Middle_Tip->SetupAttachment(RightHand);

    Ring_Tip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring Tip"));
    Ring_Tip->SetupAttachment(RightHand);

    Pinky_Tip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pinky Tip"));
    Pinky_Tip->SetupAttachment(RightHand);
}

void AVRPawn::AppendJointMeshToHandJointMeshes()
{
    HandJointMeshes.Add(FName("Wrist Root"), WristRoot);
    //HandJointMeshes.Add(FName("Forearm_Stub"), Forearm_Stub);

    HandJointMeshes.Add(FName("Thumb0"), Thumb0);
    HandJointMeshes.Add(FName("Thumb1"), Thumb1);
    HandJointMeshes.Add(FName("Thumb2"), Thumb2);
    HandJointMeshes.Add(FName("Thumb3"), Thumb3);

    HandJointMeshes.Add(FName("Index1"), Index1);
    HandJointMeshes.Add(FName("Index2"), Index2);
    HandJointMeshes.Add(FName("Index3"), Index3);

    HandJointMeshes.Add(FName("Middle1"), Middle1);
    HandJointMeshes.Add(FName("Middle2"), Middle2);
    HandJointMeshes.Add(FName("Middle3"), Middle3);

    HandJointMeshes.Add(FName("Ring1"), Ring1);
    HandJointMeshes.Add(FName("Ring2"), Ring2);
    HandJointMeshes.Add(FName("Ring3"), Ring3);

    HandJointMeshes.Add(FName("Pinky0"), Pinky0);
    HandJointMeshes.Add(FName("Pinky1"), Pinky1);
    HandJointMeshes.Add(FName("Pinky2"), Pinky2);
    HandJointMeshes.Add(FName("Pinky3"), Pinky3);

    HandJointMeshes.Add(FName("Thumb Tip"), Thumb_Tip);
    HandJointMeshes.Add(FName("Index Tip"), Index_Tip);
    HandJointMeshes.Add(FName("Middle Tip"), Middle_Tip);
    HandJointMeshes.Add(FName("Ring Tip"), Ring_Tip);
    HandJointMeshes.Add(FName("Pinky Tip"), Pinky_Tip);
}

void AVRPawn::PlaceJointMeshOnHandJoints()
{
    for (auto& Pair : HandJointMeshes)
    {
        FVector JointLocation = RightHand->GetBoneLocationByName(Pair.Key, EBoneSpaces::WorldSpace);
        FRotator JointRotation = RightHand->GetBoneRotationByName(Pair.Key, EBoneSpaces::WorldSpace);
        Pair.Value->SetWorldLocation(JointLocation);
        Pair.Value->SetWorldRotation(JointRotation);

        //UE_LOG(LogTemp, Display, TEXT("%s :  %f   %f   %f   %f   %f   %f"), *Pair.Key.ToString(), JointLocation.X, JointLocation.Y, JointLocation.Z, JointRotation.Pitch, JointRotation.Yaw, JointRotation.Roll);
        
    }
}

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

const TMap<FName, UStaticMeshComponent*>& AVRPawn::GetHandJointMeshes()
{
    return HandJointMeshes;
}


