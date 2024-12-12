// Fill out your copyright notice in the Description page of Project Settings.


#include "GGGPawn.h"

#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "OculusXRHandComponent.h"
#include "OculusXRInputFunctionLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "HandJoint.h"
#include "HandTrackingDataComponent.h"
#include "LSTMHandlerComponent.h"
#include "JointMeshComponent.h"
#include "GGGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "CommonTypes.h"

// Sets default values
AGGGPawn::AGGGPawn()
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


    // 오른손 조인트 컴포넌트 생성
    RightHandJoints = CreateDefaultSubobject<UHandJoint>(TEXT("Right Hand Joints"));
    RightHandJoints->SetupAttachment(RightHand);
    RightHandJoints->HandType = EHandType::RightHand;
    

    // 왼손 조인트 컴포넌트 생성
    LeftHandJoints = CreateDefaultSubobject<UHandJoint>(TEXT("Left Hand Joints"));
    LeftHandJoints->SetupAttachment(LeftHand);
    LeftHandJoints->HandType = EHandType::LeftHand;

    //HandTrackingDataComponent
    HandTrackingDataComponent = CreateDefaultSubobject<UHandTrackingDataComponent>(TEXT("HandTrackingDataComponent"));

    //LSTMHandlerComponent
    LSTMHandlerComponent = CreateDefaultSubobject<ULSTMHandlerComponent>(TEXT("LSTMHandlerComponent"));

    GGGGameInstance = Cast<UGGGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

}

// Called when the game starts or when spawned
void AGGGPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGGGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    PlaceJointOnXRHand();
    EnqueueJointSequenceData();

    //UE_LOG(LogTemp, Display, TEXT("JointSequenceData Num : %d"), QueueCount);
    LSTMHandlerComponent->ExecuteNNETickInference(JointSequenceData);
}

// Called to bind functionality to input
void AGGGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGGGPawn::PlaceJointOnXRHand()
{
    TArray<UJointMeshComponent*> RightJoints = RightHandJoints->GetJointArray();
    TArray<UJointMeshComponent*> LeftJoints = LeftHandJoints->GetJointArray();

    for (auto& RightJoint : RightJoints)
    {
        FQuat WristRootQuat = RightHand->GetComponentQuat();
        FVector JointLocation = RightHand->GetBoneLocation(RightJoint->GetFName(), EBoneSpaces::WorldSpace);
        FRotator JointRotation = RightHand->GetBoneRotationByName(RightJoint->GetFName(), EBoneSpaces::WorldSpace);
        
        RightJoint->SetWorldLocation(JointLocation);
        RightJoint->SetWorldRotation(JointRotation);

        USceneComponent* ParentJoint = RightJoint->GetAttachParent();
        FVector ParentJointLocation = ParentJoint->GetComponentLocation();


        FVector RelativeLocation = RightJoint->GetComponentLocation() - ParentJointLocation;
        FVector Name = WristRootQuat.RotateVector(RelativeLocation);
        //UE_LOG(LogTemp, Display, TEXT("%s"), *RightJoint->GetStaticMesh();
        
        //UE_LOG(LogTemp, Display, TEXT("ParentJoint %s"), *ParentJoint->GetName());
        //UE_LOG(LogTemp, Display, TEXT("RightJoint Location %s : %f   %f   %f"), *RightJoint->GetName(), RightJoint->GetComponentLocation().X, RightJoint->GetComponentLocation().Y, RightJoint->GetComponentLocation().Z);
        //UE_LOG(LogTemp, Display, TEXT("RightJoint Location %s : %f   %f   %f"), *RightJoint->GetName(), RelativeLocation.X, RelativeLocation.Y, RelativeLocation.Z);
        //UE_LOG(LogTemp, Display, TEXT("RightJoint Location %s : %f   %f   %f"), *RightJoint->GetName(), Name.X, Name.Y, Name.Z);
        //UE_LOG(LogTemp, Display, TEXT("RightWristRootQuatToRotator : %f   %f   %f"), WristRootQuat.Rotator().Pitch, WristRootQuat.Rotator().Yaw, WristRootQuat.Rotator().Roll);
        //UE_LOG(LogTemp, Display, TEXT("RightJoint Location : %f   %f   %f"), JointLocation.X, JointLocation.Y, JointLocation.Z);
        DrawDebugLine(GetWorld(), ParentJointLocation, JointLocation, FColor::Green, false, -1.0f);
        
    }

    for (auto& LeftJoint : LeftJoints)
    {
        FQuat WristRootQuat = LeftHand->GetComponentQuat();
        FVector JointLocation = LeftHand->GetBoneLocation(LeftJoint->GetFName(), EBoneSpaces::WorldSpace);
        FRotator JointRotation = LeftHand->GetBoneRotationByName(LeftJoint->GetFName(), EBoneSpaces::WorldSpace);

        LeftJoint->SetWorldLocation(JointLocation);
        LeftJoint->SetWorldRotation(JointRotation);

        USceneComponent* ParentJoint = LeftJoint->GetAttachParent();
        FVector ParentJointLocation = ParentJoint->GetComponentLocation();

        FVector RelativeLocation = LeftJoint->GetComponentLocation() - ParentJointLocation;
        FVector Name = WristRootQuat.RotateVector(RelativeLocation);

        //UE_LOG(LogTemp, Display, TEXT("LeftJoint Location %s : %f   %f   %f"), *LeftJoint->GetName(), LeftJoint->GetComponentLocation().X, LeftJoint->GetComponentLocation().Y, LeftJoint->GetComponentLocation().Z);
        //UE_LOG(LogTemp, Display, TEXT("LeftJoint Location %s : %f   %f   %f"), *LeftJoint->GetName(), RelativeLocation.X, RelativeLocation.Y, RelativeLocation.Z);
        //UE_LOG(LogTemp, Display, TEXT("LeftJoint Location %s : %f   %f   %f"), *LeftJoint->GetName(), Name.X, Name.Y, Name.Z);
        //UE_LOG(LogTemp, Display, TEXT("LeftWristRootQuatToRotator : %f   %f   %f"), WristRootQuat.Rotator().Pitch, WristRootQuat.Rotator().Yaw, WristRootQuat.Rotator().Roll);
        DrawDebugLine(GetWorld(), ParentJointLocation, JointLocation, FColor::Green, false, -1.0f);
    }
}

void AGGGPawn::EnqueueJointSequenceData()
{
    TArray<UJointMeshComponent*> RightJoints = RightHandJoints->GetJointArray();
    TArray<UJointMeshComponent*> LeftJoints = LeftHandJoints->GetJointArray();
    
    TArray<float> JointDatas;


    /*for (int i = 0; i < RightJoints.Num(); i++)
    {
        if (i == 0)
        {
            FVector R_WristRoot_Loc_Acc = RightJoints[0]->GetComponentLocation() - PreRightHandLocation;
            FQuat R_WristRoot_Quat_Acc = RightJoints[0]->GetComponentQuat() * PreRightHandQuat.Inverse();
            FRotator R_WristRoot_Rot_Acc = R_WristRoot_Quat_Acc.Rotator();

            FVector L_WristRoot_Loc_Acc = LeftJoints[0]->GetComponentLocation() - PreLeftHandLocation;
            FQuat L_WristRoot_Quat_Acc = LeftJoints[0]->GetComponentQuat() * PreLeftHandQuat.Inverse();
            FRotator L_WristRoot_Rot_Acc = L_WristRoot_Quat_Acc.Rotator();

            JointDatas.Add(R_WristRoot_Loc_Acc.X);
            JointDatas.Add(R_WristRoot_Loc_Acc.Y);
            JointDatas.Add(R_WristRoot_Loc_Acc.Z);

            JointDatas.Add(L_WristRoot_Loc_Acc.X);
            JointDatas.Add(L_WristRoot_Loc_Acc.Y);
            JointDatas.Add(L_WristRoot_Loc_Acc.Z);

            JointDatas.Add(R_WristRoot_Rot_Acc.Pitch);
            JointDatas.Add(R_WristRoot_Rot_Acc.Yaw);
            JointDatas.Add(R_WristRoot_Rot_Acc.Roll);

            JointDatas.Add(L_WristRoot_Rot_Acc.Pitch);
            JointDatas.Add(L_WristRoot_Rot_Acc.Yaw);
            JointDatas.Add(L_WristRoot_Rot_Acc.Roll);
        }
        else
        {
            FVector R_RightJoint_Rel_Loc = RightJoints[i]->GetRelativeLocation();
            FVector L_RightJoint_Rel_Loc = RightJoints[i]->GetRelativeLocation();

            JointDatas.Add(R_RightJoint_Rel_Loc.X);
            JointDatas.Add(R_RightJoint_Rel_Loc.Y);
            JointDatas.Add(R_RightJoint_Rel_Loc.Z);

            JointDatas.Add(L_RightJoint_Rel_Loc.X);
            JointDatas.Add(L_RightJoint_Rel_Loc.Y);
            JointDatas.Add(L_RightJoint_Rel_Loc.Z);
        }
    }

    PreRightHandLocation = RightJoints[0]->GetComponentLocation();
    PreRightHandQuat = RightJoints[0]->GetComponentQuat();
    PreLeftHandLocation = LeftJoints[0]->GetComponentLocation();
    PreLeftHandQuat = LeftJoints[0]->GetComponentQuat();


    JointSequenceData.Enqueue(JointDatas);
    QueueCount++;

    if (QueueCount > GGGGameInstance->TimeStep)
    {
        JointSequenceData.Pop();
        QueueCount--;
    }*/


    for (int i = 0; i < RightJoints.Num(); i++)
    {

        if (i == 5 || i == 9 || i == 13 || i == 17 || i == 22)
        {

        }
        else if (i == 0)
        {
            FVector R_WristRoot_Loc_Acc = RightJoints[0]->GetComponentLocation() - PreRightHandLocation;
            FQuat R_WristRoot_Quat_Acc = RightJoints[0]->GetComponentQuat() * PreRightHandQuat.Inverse();
            FRotator R_WristRoot_Rot_Acc = R_WristRoot_Quat_Acc.Rotator();

            FVector L_WristRoot_Loc_Acc = LeftJoints[0]->GetComponentLocation() - PreLeftHandLocation;
            FQuat L_WristRoot_Quat_Acc = LeftJoints[0]->GetComponentQuat() * PreLeftHandQuat.Inverse();
            FRotator L_WristRoot_Rot_Acc = L_WristRoot_Quat_Acc.Rotator();

            JointDatas.Add(R_WristRoot_Loc_Acc.X);
            JointDatas.Add(R_WristRoot_Loc_Acc.Y);
            JointDatas.Add(R_WristRoot_Loc_Acc.Z);

            JointDatas.Add(L_WristRoot_Loc_Acc.X);
            JointDatas.Add(L_WristRoot_Loc_Acc.Y);
            JointDatas.Add(L_WristRoot_Loc_Acc.Z);

            JointDatas.Add(R_WristRoot_Rot_Acc.Pitch);
            JointDatas.Add(R_WristRoot_Rot_Acc.Yaw);
            JointDatas.Add(R_WristRoot_Rot_Acc.Roll);

            JointDatas.Add(L_WristRoot_Rot_Acc.Pitch);
            JointDatas.Add(L_WristRoot_Rot_Acc.Yaw);
            JointDatas.Add(L_WristRoot_Rot_Acc.Roll);
        }
        else
        {
            ////////////////////// 회전 계산.
            FQuat R_RightJoint_Qaut = RightJoints[i]->GetComponentQuat();
            FQuat L_RightJoint_Qaut = LeftJoints[i]->GetComponentQuat();

            USceneComponent* R_ParentComponent = RightJoints[i]->GetAttachParent();
            USceneComponent* L_ParentComponent = LeftJoints[i]->GetAttachParent();

            FQuat R_Parent_RightJoint_Quat = R_ParentComponent->GetComponentQuat();
            FQuat L_Parent_LeftJoint_Quat = L_ParentComponent->GetComponentQuat();

            FRotator R_RightJoint_Rot = (R_Parent_RightJoint_Quat.Inverse() * R_RightJoint_Qaut).Rotator();
            FRotator L_RightJoint_Rot = (L_Parent_LeftJoint_Quat.Inverse() * L_RightJoint_Qaut).Rotator();


            //FVector R_RightJoint_Rel_Loc = RightJoints[i]->GetRelativeLocation();
            //FVector L_RightJoint_Rel_Loc = RightJoints[i]->GetRelativeLocation();

            JointDatas.Add(R_RightJoint_Rot.Pitch);
            JointDatas.Add(R_RightJoint_Rot.Yaw);
            JointDatas.Add(R_RightJoint_Rot.Roll);

            JointDatas.Add(L_RightJoint_Rot.Pitch);
            JointDatas.Add(L_RightJoint_Rot.Yaw);
            JointDatas.Add(L_RightJoint_Rot.Roll);

        }
    }

    PreRightHandLocation = RightJoints[0]->GetComponentLocation();
    PreRightHandQuat = RightJoints[0]->GetComponentQuat();
    PreLeftHandLocation = LeftJoints[0]->GetComponentLocation();
    PreLeftHandQuat = LeftJoints[0]->GetComponentQuat();


    JointSequenceData.Enqueue(JointDatas);
    QueueCount++;

    if (QueueCount > GGGGameInstance->TimeStep)
    {
        JointSequenceData.Pop();
        QueueCount--;
    }
}

