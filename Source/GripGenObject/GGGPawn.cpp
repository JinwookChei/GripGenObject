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

// Sets default values
AGGGPawn::AGGGPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // ��Ʈ ������Ʈ ����
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = Root;

    // ī�޶� ������Ʈ ���� �� ����
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(Root);

    // �ʱ� ��ġ ���� (�ʿ� ��)
    //CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f)); // ��: Pawn�� �Ӹ� ����
    //CameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); // �ణ �Ʒ��� ���ϵ��� ����

    // ������ Motion Controller ����
    RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
    RightController->SetupAttachment(Root);
    RightController->SetTrackingSource(EControllerHand::Right); // ������ ����

    // �޼� Motion Controller ����
    LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
    LeftController->SetupAttachment(Root);
    LeftController->SetTrackingSource(EControllerHand::Left); // �޼� ����

    // ������ OculusXR Hand ������Ʈ ����
    RightHand = CreateDefaultSubobject<UOculusXRHandComponent>(TEXT("RightHand"));
    RightHand->SetupAttachment(RightController);
    RightHand->SkeletonType = EOculusXRHandType::HandRight;

    // �޼� OculusXR Hand ������Ʈ ����
    LeftHand = CreateDefaultSubobject<UOculusXRHandComponent>(TEXT("LeftHand"));
    LeftHand->SetupAttachment(LeftController);
    LeftHand->SkeletonType = EOculusXRHandType::HandLeft;

    // ������ ����Ʈ ������Ʈ ����
    RightHandJoints = CreateDefaultSubobject<UHandJoint>(TEXT("Right Hand Joints"));
    RightHandJoints->SetupAttachment(RightHand);
    RightHandJoints->HandType = EHandType::RightHand;

    // �޼� ����Ʈ ������Ʈ ����
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
    //LSTMHandlerComponent->ExecuteNNETickInference();
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
        FVector JointLocation = RightHand->GetBoneLocation(RightJoint->GetFName(), EBoneSpaces::WorldSpace);
        FRotator JointRotation = RightHand->GetBoneRotationByName(RightJoint->GetFName(), EBoneSpaces::WorldSpace);
        
        RightJoint->SetWorldLocation(JointLocation);
        RightJoint->SetWorldRotation(JointRotation);

        USceneComponent* ParentJoint = RightJoint->GetAttachParent();
        FVector ParentJointLocation = ParentJoint->GetComponentLocation();

        DrawDebugLine(GetWorld(), ParentJointLocation, JointLocation, FColor::Green, false, -1.0f);
        
    }

    for (auto& LeftJoint : LeftJoints)
    {
        FVector JointLocation = RightHand->GetBoneLocation(LeftJoint->GetFName(), EBoneSpaces::WorldSpace);
        FRotator JointRotation = RightHand->GetBoneRotationByName(LeftJoint->GetFName(), EBoneSpaces::WorldSpace);

        LeftJoint->SetWorldLocation(JointLocation);
        LeftJoint->SetWorldRotation(JointRotation);

        USceneComponent* ParentJoint = LeftJoint->GetAttachParent();
        FVector ParentJointLocation = ParentJoint->GetComponentLocation();

        DrawDebugLine(GetWorld(), ParentJointLocation, JointLocation, FColor::Green, false, -1.0f);
    }
}

void AGGGPawn::EnqueueJointSequenceData()
{
    TArray<UJointMeshComponent*> RightJoints = RightHandJoints->GetJointArray();
    TArray<UJointMeshComponent*> LeftJoints = LeftHandJoints->GetJointArray();
    
    TArray<float> JointDatas;


    for (int i = 0; i < RightJoints.Num(); i++)
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
    }
}
