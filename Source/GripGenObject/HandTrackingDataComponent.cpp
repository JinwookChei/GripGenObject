// Fill out your copyright notice in the Description page of Project Settings.


#include "HandTrackingDataComponent.h"
#include "VRPawn.h"
#include "OculusXRHandComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "JointMeshComponent.h"
#include "HandJoint.h"
#include "TimerManager.h"
#include "GGGGameInstance.h"
#include "CommonTypes.h"

        


// Sets default values for this component's properties
UHandTrackingDataComponent::UHandTrackingDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
    UGGGGameInstance* GGGGameInstance = Cast<UGGGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (GGGGameInstance)
    {
        LearningSampleNum = GGGGameInstance->LearningSampleNum;

        TimeStep = GGGGameInstance->TimeStep;
    }
    else
    {
        LearningSampleNum = 0;
        TimeStep = 0;
    }
}


// Called when the game starts
void UHandTrackingDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
    //OwnerRightHand = UGameplayStatics::GetPlayerCharacter(this, 0);

    
    OwnerPawn = Cast<AVRPawn>(GetOwner());
    if (OwnerPawn)
    {
        OwnerRightHand = OwnerPawn->GetOculusHand(EHandType::RightHand);
        OwnerLeftHand = OwnerPawn->GetOculusHand(EHandType::LeftHand);

        HandJointMeshes = OwnerPawn->GetHandJointMeshes();
    }

    TickCount = 9999;
    LearningSampleCount = 9999;
}


// Called every frame
void UHandTrackingDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    //CalculateRelativeJoint();

    ExportHandDatasToCSV_Loop();
}

void UHandTrackingDataComponent::StartWriteCSVData(EHandDataLabel _HandDataLabel, UHandJoint* _RightHandJoint, UHandJoint* _LeftHandJoint)
{
    HandDataLabel = _HandDataLabel;
    RightHandJoint = _RightHandJoint;
    LeftHandJoint = _LeftHandJoint;
    

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
        {
            Initialize_CSVData();
        }, 3.0f, false);
}

void UHandTrackingDataComponent::Initialize_CSVData()
{
    TickCount = 0;
    LearningSampleCount = 0;

    // 저장 폴더 경로 지정 (Saved/HandTrackingData)
    FString Directory = FPaths::Combine(FPaths::ProjectDir(), TEXT("HandTrackingData"));

    // 디렉터리 생성 (없는 경우)
    if (!IFileManager::Get().DirectoryExists(*Directory))
    {
        IFileManager::Get().MakeDirectory(*Directory, true);
    }

    // 파일 경로 지정
    Filename = FPaths::Combine(Directory, TEXT("JointData.csv"));


    // ----------------------------------- 한손, Rotator, Location 둘다 사용 버전 ----------------------------------------------------
    //// Initialize the CSV data string with the header (optional, but useful for clarity)
    //CSVData = TEXT("WristRoot_Pitch,WristRoot_Yaw,WristRoot_Roll,WristRoot_X,WristRoot_Y,WristRoot_Z,");

    //CSVData += TEXT("Thumb0_Rotation_Pitch,Thumb0_Rotation_Yaw,Thumb0_Rotation_Roll,Thumb0_Location_X,Thumb0_Location_Y,Thumb0_Location_Z,");
    //CSVData += TEXT("Thumb1_Rotation_Pitch,Thumb1_Rotation_Yaw,Thumb1_Rotation_Roll,Thumb1_Location_X,Thumb1_Location_Y,Thumb1_Location_Z,");
    //CSVData += TEXT("Thumb2_Rotation_Pitch,Thumb2_Rotation_Yaw,Thumb2_Rotation_Roll,Thumb2_Location_X,Thumb2_Location_Y,Thumb2_Location_Z,");
    //CSVData += TEXT("Thumb3_Rotation_Pitch,Thumb3_Rotation_Yaw,Thumb3_Rotation_Roll,Thumb3_Location_X,Thumb3_Location_Y,Thumb3_Location_Z,");
    //CSVData += TEXT("Thumb_Tip_Rotation_Pitch,Thumb_Tip_Rotation_Yaw,Thumb_Tip_Rotation_Roll,Thumb_Tip_Location_X,Thumb_Tip_Location_Y,Thumb_Tip_Location_Z,");

    //CSVData += TEXT("Index1_Rotation_Pitch,Index1_Rotation_Yaw,Index1_Rotation_Roll,Index1_Location_X,Index1_Location_Y,Index1_Location_Z,");
    //CSVData += TEXT("Index2_Rotation_Pitch,Index2_Rotation_Yaw,Index2_Rotation_Roll,Index2_Location_X,Index2_Location_Y,Index2_Location_Z,");
    //CSVData += TEXT("Index3_Rotation_Pitch,Index3_Rotation_Yaw,Index3_Rotation_Roll,Index3_Location_X,Index3_Location_Y,Index3_Location_Z,");
    //CSVData += TEXT("Index_Tip_Rotation_Pitch,Index_Tip_Rotation_Yaw,Index_Tip_Rotation_Roll,Index_Tip_Location_X,Index_Tip_Location_Y,Index_Tip_Location_Z,");

    //CSVData += TEXT("Middle1_Rotation_Pitch,Middle1_Rotation_Yaw,Middle1_Rotation_Roll,Middle1_Location_X,Middle1_Location_Y,Middle1_Location_Z,");
    //CSVData += TEXT("Middle2_Rotation_Pitch,Middle2_Rotation_Yaw,Middle2_Rotation_Roll,Middle2_Location_X,Middle2_Location_Y,Middle2_Location_Z,");
    //CSVData += TEXT("Middle3_Rotation_Pitch,Middle3_Rotation_Yaw,Middle3_Rotation_Roll,Middle3_Location_X,Middle3_Location_Y,Middle3_Location_Z,");
    //CSVData += TEXT("Middle_Tip_Rotation_Pitch,Middle_Tip_Rotation_Yaw,Middle_Tip_Rotation_Roll,Middle_Tip_Location_X,Middle_Tip_Location_Y,Middle_Tip_Location_Z,");

    //CSVData += TEXT("Ring1_Rotation_Pitch,Ring1_Rotation_Yaw,Ring1_Rotation_Roll,Ring1_Location_X,Ring1_Location_Y,Ring1_Location_Z,");
    //CSVData += TEXT("Ring2_Rotation_Pitch,Ring2_Rotation_Yaw,Ring2_Rotation_Roll,Ring2_Location_X,Ring2_Location_Y,Ring2_Location_Z,");
    //CSVData += TEXT("Ring3_Rotation_Pitch,Ring3_Rotation_Yaw,Ring3_Rotation_Roll,Ring3_Location_X,Ring3_Location_Y,Ring3_Location_Z,");
    //CSVData += TEXT("Ring_Tip_Rotation_Pitch,Ring_Tip_Rotation_Yaw,Ring_Tip_Rotation_Roll,Ring_Tip_Location_X,Ring_Tip_Location_Y,Ring_Tip_Location_Z,");

    //CSVData += TEXT("Pinky0_Rotation_Pitch,Pinky0_Rotation_Yaw,Pinky0_Rotation_Roll,Pinky0_Location_X,Pinky0_Location_Y,Pinky0_Location_Z,");
    //CSVData += TEXT("Pinky1_Rotation_Pitch,Pinky1_Rotation_Yaw,Pinky1_Rotation_Roll,Pinky1_Location_X,Pinky1_Location_Y,Pinky1_Location_Z,");
    //CSVData += TEXT("Pinky2_Rotation_Pitch,Pinky2_Rotation_Yaw,Pinky2_Rotation_Roll,Pinky2_Location_X,Pinky2_Location_Y,Pinky2_Location_Z,");
    //CSVData += TEXT("Pinky3_Rotation_Pitch,Pinky3_Rotation_Yaw,Pinky3_Rotation_Roll,Pinky3_Location_X,Pinky3_Location_Y,Pinky3_Location_Z,");
    //CSVData += TEXT("Pinky_Tip_Rotation_Pitch,Pinky_Tip_Rotation_Yaw,Pinky_Tip_Rotation_Roll,Pinky_Tip_Location_X,Pinky_Tip_Location_Y,Pinky_Tip_Location_Z,");
    //
    //CSVData += TEXT("Label\n");

    // ----------------------------------- 양손, Rotator없이, Location vector 사용 버전 ----------------------------------------------------
    CSVData = TEXT("R_WristRoot_Loc_Acc_X,R_WristRoot_Loc_Acc_Y,R_WristRoot_Loc_Acc_Z,");
    CSVData += TEXT("L_WristRoot_Loc_Acc_X,L_WristRoot_Loc_Acc_Y,L_WristRoot_Loc_Acc_Z,");
    CSVData += TEXT("R_WristRoot_Rot_Acc_X,R_WristRoot_Rot_Acc_Y,R_WristRoot_Rot_Acc_Z,");
    CSVData += TEXT("L_WristRoot_Rot_Acc_X,L_WristRoot_Rot_Acc_Y,L_WristRoot_Rot_Acc_Z,");


    CSVData += TEXT("R_Thumb0_Relative_Loc_X,R_Thumb0_Relative_Loc_Y,R_Thumb0_Relative_Loc_Z,");
    CSVData += TEXT("L_Thumb0_Relative_Loc_X,L_Thumb0_Relative_Loc_Y,L_Thumb0_Relative_Loc_Z,");
    CSVData += TEXT("R_Thumb1_Relative_Loc_X,R_Thumb1_Relative_Loc_Y,R_Thumb1_Relative_Loc_Z,");
    CSVData += TEXT("L_Thumb1_Relative_Loc_X,L_Thumb1_Relative_Loc_Y,L_Thumb1_Relative_Loc_Z,");
    CSVData += TEXT("R_Thumb2_Relative_Loc_X,R_Thumb2_Relative_Loc_Y,R_Thumb2_Relative_Loc_Z,");
    CSVData += TEXT("L_Thumb2_Relative_Loc_X,L_Thumb2_Relative_Loc_Y,L_Thumb2_Relative_Loc_Z,");
    CSVData += TEXT("R_Thumb3_Relative_Loc_X,R_Thumb3_Relative_Loc_Y,R_Thumb3_Relative_Loc_Z,");
    CSVData += TEXT("L_Thumb3_Relative_Loc_X,L_Thumb3_Relative_Loc_Y,L_Thumb3_Relative_Loc_Z,");
    //CSVData += TEXT("R_Thumb_Tip_Relative_Loc_X,R_Thumb_Tip_Relative_Loc_Y,R_Thumb_Tip_Relative_Loc_Z,");
    //CSVData += TEXT("L_Thumb_Tip_Relative_Loc_X,L_Thumb_Tip_Relative_Loc_Y,L_Thumb_Tip_Relative_Loc_Z,");


    CSVData += TEXT("R_Index1_Relative_Loc_X,R_Index1_Relative_Loc_Y,R_Index1_Relative_Loc_Z,");
    CSVData += TEXT("L_Index1_Relative_Loc_X,L_Index1_Relative_Loc_Y,L_Index1_Relative_Loc_Z,");
    CSVData += TEXT("R_Index2_Relative_Loc_X,R_Index2_Relative_Loc_Y,R_Index2_Relative_Loc_Z,");
    CSVData += TEXT("L_Index2_Relative_Loc_X,L_Index2_Relative_Loc_Y,L_Index2_Relative_Loc_Z,");
    CSVData += TEXT("R_Index3_Relative_Loc_X,R_Index3_Relative_Loc_Y,R_Index3_Relative_Loc_Z,");
    CSVData += TEXT("L_Index3_Relative_Loc_X,L_Index3_Relative_Loc_Y,L_Thumb3_Relative_Loc_Z,");
    //CSVData += TEXT("R_Index_Tip_Relative_Loc_X,R_Index_Tip_Relative_Loc_Y,R_Index_Tip_Relative_Loc_Z,");
    //CSVData += TEXT("L_Index_Tip_Relative_Loc_X,L_Index_Tip_Relative_Loc_Y,L_Index_Tip_Relative_Loc_Z,");


    CSVData += TEXT("R_Middle1_Relative_Loc_X,R_Middle1_Relative_Loc_Y,R_Middle1_Relative_Loc_Z,");
    CSVData += TEXT("L_Middle1_Relative_Loc_X,L_Middle1_Relative_Loc_Y,L_Middle1_Relative_Loc_Z,");
    CSVData += TEXT("R_Middle2_Relative_Loc_X,R_Middle2_Relative_Loc_Y,R_Middle2_Relative_Loc_Z,");
    CSVData += TEXT("L_Middle2_Relative_Loc_X,L_Middle2_Relative_Loc_Y,L_Middle2_Relative_Loc_Z,");
    CSVData += TEXT("R_Middle3_Relative_Loc_X,R_Middle3_Relative_Loc_Y,R_Middle3_Relative_Loc_Z,");
    CSVData += TEXT("L_Middle3_Relative_Loc_X,L_Middle3_Relative_Loc_Y,L_Middle3_Relative_Loc_Z,");
    //CSVData += TEXT("R_Middle_Tip_Relative_Loc_X,R_Middle_Tip_Relative_Loc_Y,R_Middle_Tip_Relative_Loc_Z,");
    //CSVData += TEXT("L_Middle_Tip_Relative_Loc_X,L_Middle_Tip_Relative_Loc_Y,L_Middle_Tip_Relative_Loc_Z,");


    CSVData += TEXT("R_Ring1_Relative_Loc_X,R_Ring1_Relative_Loc_Y,R_Ring1_Relative_Loc_Z,");
    CSVData += TEXT("L_Ring1_Relative_Loc_X,L_Ring1_Relative_Loc_Y,L_Ring1_Relative_Loc_Z,");
    CSVData += TEXT("R_Ring2_Relative_Loc_X,R_Ring2_Relative_Loc_Y,R_Ring2_Relative_Loc_Z,");
    CSVData += TEXT("L_Ring2_Relative_Loc_X,L_Ring2_Relative_Loc_Y,L_Ring2_Relative_Loc_Z,");
    CSVData += TEXT("R_Ring3_Relative_Loc_X,R_Ring3_Relative_Loc_Y,R_Ring3_Relative_Loc_Z,");
    CSVData += TEXT("L_Ring3_Relative_Loc_X,L_Ring3_Relative_Loc_Y,L_Ring3_Relative_Loc_Z,");
    //CSVData += TEXT("R_Ring_Tip_Relative_Loc_X,R_Ring_Tip_Relative_Loc_Y,R_Ring_Tip_Relative_Loc_Z,");
    //CSVData += TEXT("L_Ring_Tip_Relative_Loc_X,L_Ring_Tip_Relative_Loc_Y,L_Ring_Tip_Relative_Loc_Z,");


    CSVData += TEXT("R_Pinky0_Relative_Loc_X,R_Pinky0_Relative_Loc_Y,R_Pinky0_Relative_Loc_Z,");
    CSVData += TEXT("L_Pinky0_Relative_Loc_X,L_Pinky0_Relative_Loc_Y,L_Pinky0_Relative_Loc_Z,");
    CSVData += TEXT("R_Pinky1_Relative_Loc_X,R_Pinky1_Relative_Loc_Y,R_Pinky1_Relative_Loc_Z,");
    CSVData += TEXT("L_Pinky1_Relative_Loc_X,L_Pinky1_Relative_Loc_Y,L_Pinky1_Relative_Loc_Z,");
    CSVData += TEXT("R_Pinky2_Relative_Loc_X,R_Pinky2_Relative_Loc_Y,R_Pinky2_Relative_Loc_Z,");
    CSVData += TEXT("L_Pinky2_Relative_Loc_X,L_Pinky2_Relative_Loc_Y,L_Pinky2_Relative_Loc_Z,");
    CSVData += TEXT("R_Pinky3_Relative_Loc_X,R_Pinky3_Relative_Loc_Y,R_Pinky3_Relative_Loc_Z,");
    CSVData += TEXT("L_Pinky3_Relative_Loc_X,L_Pinky3_Relative_Loc_Y,L_Pinky3_Relative_Loc_Z,");
    //CSVData += TEXT("R_Pinky_Tip_Relative_Loc_X,R_Pinky_Tip_Relative_Loc_Y,R_Pinky_Tip_Relative_Loc_Z,");
    //CSVData += TEXT("L_Pinky_Tip_Relative_Loc_X,L_Pinky_Tip_Relative_Loc_Y,L_Pinky_Tip_Relative_Loc_Z,");
    

    CSVData += TEXT("Label\n");



    // 메시지 내용, 메시지 키, 출력 시간(초), 텍스트 색상 지정
    FString Message = TEXT("Start Data Cap!");
    FColor TextColor = FColor::Green;
    float DisplayTime = 5.0f; // 5초 동안 표시

    // 메시지 출력 (키는 0부터 9999까지 임의로 설정 가능)
    GEngine->AddOnScreenDebugMessage(-1, DisplayTime, TextColor, Message);
}

void UHandTrackingDataComponent::ExportHandDatasToCSV(UOculusXRHandComponent* _Hand, TArray<UJointMeshComponent*>& _HandJointMeshes, EHandDataLabel _HandDataLabel)
{
    for (auto& HandJointMesh : _HandJointMeshes)
    {
        FVector JointLocation;
        FRotator JointRotation;
        if(HandJointMesh->GetName() == "Wrist Root")
        {
            UCameraComponent* OwnerCameraComponent = OwnerPawn->GetComponentByClass<UCameraComponent>();
            //FTransform CameraTransform = OwnerCameraComponent->GetComponentTransform();
            FVector CameraLocation = OwnerCameraComponent->GetComponentLocation();
            FQuat CameraQuat = OwnerCameraComponent->GetComponentQuat();

            FVector RightHandLocation = OwnerRightHand->GetBoneLocationByName(HandJointMesh->GetFName(), EBoneSpaces::WorldSpace);
            //FRotator RightHandRotation = OwnerRightHand->GetBoneRotationByName(HandJointMesh->GetFName(), EBoneSpaces::WorldSpace);
            FQuat RightHandQuat = OwnerRightHand->GetBoneQuaternion(HandJointMesh->GetFName(), EBoneSpaces::WorldSpace);

            JointLocation = RightHandLocation - CameraLocation;
            FQuat RelativeQuat = RightHandQuat * CameraQuat.Inverse();
            JointRotation = RelativeQuat.Rotator();

            //JointLocation = CameraTransform.GetLocation() - RightHandLocation;
            //JointRotation = CameraTransform.InverseTransformRotation(RightHandRotation.Quaternion()).Rotator();
        }
        else
        {
            JointLocation = OwnerRightHand->GetBoneLocationByName(HandJointMesh->GetFName(), EBoneSpaces::ComponentSpace);
            JointRotation = OwnerRightHand->GetBoneRotationByName(HandJointMesh->GetFName(), EBoneSpaces::ComponentSpace);
        }
        
        CSVData += FString::Printf(TEXT("%f,%f,%f,%f,%f,%f,"), JointRotation.Pitch, JointRotation.Yaw, JointRotation.Roll, JointLocation.X, JointLocation.Y, JointLocation.Z);
    }

    switch (_HandDataLabel)
    {
        case EHandDataLabel::Idle:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Idle);
            break;
        case EHandDataLabel::Pistol:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Pistol);
            break;
        case EHandDataLabel::Drill:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Drill);
            break;
        case EHandDataLabel::Sword:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Sword);
            break;
        case EHandDataLabel::Dagger:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Dagger);
            break;
        case EHandDataLabel::KitchenKnife:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::KitchenKnife);
            break;
        default:
            break;
    }
    

    // Save the CSV data to the file
    if (FFileHelper::SaveStringToFile(CSVData, *Filename))
    {
        UE_LOG(LogTemp, Log, TEXT("CSV file created successfully at %s"), *Filename);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create CSV file at %s"), *Filename);
    }

    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Writing Hand Data File"));
}

void UHandTrackingDataComponent::ExportRelativeHandDatasToCSV()
{
    //for (int i = 0; i < HandJointMeshes.Num(); i++)
    //{
    //    CSVData += FString::Printf(TEXT("%f,%f,%f,"), HandJointRelativeRotations[i].Pitch, HandJointRelativeRotations[i].Yaw, HandJointRelativeRotations[i].Roll);
    //    CSVData += FString::Printf(TEXT("%f,%f,%f,"), HandJointRelativeLocations[i].X, HandJointRelativeLocations[i].Y, HandJointRelativeLocations[i].Z);
    //}

    //switch (_HandDataLabel)
    //{
    //case EHandDataLabel::Idle:
    //    CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Idle);
    //    break;
    //case EHandDataLabel::Pistol:
    //    CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Pistol);
    //    break;
    //case EHandDataLabel::Drill:
    //    CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Drill);
    //    break;
    //case EHandDataLabel::Sword:
    //    CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Sword);
    //    break;
    //case EHandDataLabel::Dagger:
    //    CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Dagger);
    //    break;
    //case EHandDataLabel::KitchenKnife:
    //    CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::KitchenKnife);
    //    break;
    //default:
    //    break;
    //}

    //// Save the CSV data to the file
    //if (FFileHelper::SaveStringToFile(CSVData, *Filename))
    //{
    //    UE_LOG(LogTemp, Log, TEXT("CSV file created successfully at %s"), *Filename);
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Error, TEXT("Failed to create CSV file at %s"), *Filename);
    //}

    //GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Writing Hand Data File"));

    //--------------------------------------------- 양손 Location 만 사용한 버전 ------------------------------------------------------


    TArray<UJointMeshComponent*> RightJointArray = RightHandJoint->GetJointArray();
    TArray<UJointMeshComponent*> LeftJointArray = LeftHandJoint->GetJointArray();
    for (int i = 0; i < RightJointArray.Num(); i++)
    {
        if (i == 5 || i==9 || i==13 || i==17 || i==22)
        {

        }
        else if(i == 0)
        {
            FVector R_WristRoot_Loc_Acc = RightJointArray[0]->GetComponentLocation() - PreRightHandLocation;
            FQuat R_WristRoot_Quat_Acc = RightJointArray[0]->GetComponentQuat() * PreRightHandQuat.Inverse();
            FRotator R_WristRoot_Rot_Acc = R_WristRoot_Quat_Acc.Rotator();

            FVector L_WristRoot_Loc_Acc = LeftJointArray[0]->GetComponentLocation() - PreLeftHandLocation;
            FQuat L_WristRoot_Quat_Acc = LeftJointArray[0]->GetComponentQuat() * PreLeftHandQuat.Inverse();
            FRotator L_WristRoot_Rot_Acc = L_WristRoot_Quat_Acc.Rotator();

            CSVData += FString::Printf(TEXT("%f,%f,%f,"), R_WristRoot_Loc_Acc.X, R_WristRoot_Loc_Acc.Y, R_WristRoot_Loc_Acc.Z);
            CSVData += FString::Printf(TEXT("%f,%f,%f,"), L_WristRoot_Loc_Acc.X, L_WristRoot_Loc_Acc.Y, L_WristRoot_Loc_Acc.Z);

            CSVData += FString::Printf(TEXT("%f,%f,%f,"), R_WristRoot_Rot_Acc.Pitch, R_WristRoot_Rot_Acc.Yaw, R_WristRoot_Rot_Acc.Roll);
            CSVData += FString::Printf(TEXT("%f,%f,%f,"), L_WristRoot_Rot_Acc.Pitch, L_WristRoot_Rot_Acc.Yaw, L_WristRoot_Rot_Acc.Roll);
        }
        else
        {
            ///*FVector R_RightJoint_Rel_Loc = RightJointArray[i]->GetRelativeLocation();
            //FVector L_RightJoint_Rel_Loc = LeftJointArray[i]->GetRelativeLocation();*/

            //FVector R_RightJoint_Loc = RightJointArray[i]->GetComponentLocation();
            //FVector L_RightJoint_Loc = LeftJointArray[i]->GetComponentLocation();

            //FQuat R_WristRootQuat = RightJointArray[0]->GetComponentQuat();
            //FQuat L_WristRootQuat = LeftJointArray[0]->GetComponentQuat();

            //USceneComponent* R_ParentComponent= RightJointArray[i]->GetAttachParent();
            //USceneComponent* L_ParentComponent = LeftJointArray[i]->GetAttachParent();

            //FVector R_ParentJointLocation = R_ParentComponent->GetComponentLocation();
            //FVector L_ParentJointLocation = L_ParentComponent->GetComponentLocation();

            //FVector R_RelativeLocation = R_RightJoint_Loc - R_ParentJointLocation;
            //FVector L_RelativeLocation = L_RightJoint_Loc - L_ParentJointLocation;

            //R_RelativeLocation = R_WristRootQuat.RotateVector(R_RelativeLocation);
            //L_RelativeLocation = L_WristRootQuat.RotateVector(L_RelativeLocation);


            ///*CSVData += FString::Printf(TEXT("%f,%f,%f,"), R_RightJoint_Rel_Loc.X, R_RightJoint_Rel_Loc.Y, R_RightJoint_Rel_Loc.Z);
            //CSVData += FString::Printf(TEXT("%f,%f,%f,"), L_RightJoint_Rel_Loc.X, L_RightJoint_Rel_Loc.Y, L_RightJoint_Rel_Loc.Z);*/

            //CSVData += FString::Printf(TEXT("%f,%f,%f,"), R_RelativeLocation.X, R_RelativeLocation.Y, R_RelativeLocation.Z);
            //CSVData += FString::Printf(TEXT("%f,%f,%f,"), L_RelativeLocation.X, L_RelativeLocation.Y, L_RelativeLocation.Z);


            ////////////////////// 회전 계산.
            FQuat R_RightJoint_Qaut = RightJointArray[i]->GetComponentQuat();
            FQuat L_RightJoint_Qaut = LeftJointArray[i]->GetComponentQuat();

            USceneComponent* R_ParentComponent= RightJointArray[i]->GetAttachParent();
            USceneComponent* L_ParentComponent = LeftJointArray[i]->GetAttachParent();

            FQuat R_Parent_RightJoint_Quat = R_ParentComponent->GetComponentQuat();
            FQuat L_Parent_LeftJoint_Quat = L_ParentComponent->GetComponentQuat();

            FRotator R_RightJoint_Rot = (R_Parent_RightJoint_Quat.Inverse() * R_RightJoint_Qaut).Rotator();
            FRotator L_RightJoint_Rot = (L_Parent_LeftJoint_Quat.Inverse() * L_RightJoint_Qaut).Rotator();

            CSVData += FString::Printf(TEXT("%f,%f,%f,"), R_RightJoint_Rot.Pitch, R_RightJoint_Rot.Yaw, R_RightJoint_Rot.Roll);
            CSVData += FString::Printf(TEXT("%f,%f,%f,"), L_RightJoint_Rot.Pitch, L_RightJoint_Rot.Yaw, L_RightJoint_Rot.Roll);

            /*FRotator R_RightJoint_Rel_Rot = 
            FRotator L_RightJoint_Rel_Rot*/

        }
    }

    PreRightHandLocation = RightJointArray[0]->GetComponentLocation();
    PreRightHandQuat = RightJointArray[0]->GetComponentQuat();
    PreLeftHandLocation = LeftJointArray[0]->GetComponentLocation();
    PreLeftHandQuat = LeftJointArray[0]->GetComponentQuat();

    switch (HandDataLabel)
    {
        case EHandDataLabel::Idle:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Idle);
            break;
        case EHandDataLabel::Pistol:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Pistol);
            break;
        case EHandDataLabel::Drill:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Drill);
            break;
        case EHandDataLabel::Sword:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Sword);
            break;
        case EHandDataLabel::Dagger:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::Dagger);
            break;
        case EHandDataLabel::KitchenKnife:
            CSVData += FString::Printf(TEXT("%d\n"), EHandDataLabel::KitchenKnife);
            break;
        default:
            break;
    }   

    // Save the CSV data to the file
    if (FFileHelper::SaveStringToFile(CSVData, *Filename))
    {
        UE_LOG(LogTemp, Log, TEXT("CSV file created successfully at %s"), *Filename);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create CSV file at %s"), *Filename);
    }

    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Writing Hand Data File"));
}

void UHandTrackingDataComponent::ExportHandDatasToCSV_Loop()
{

    if (LearningSampleCount >= LearningSampleNum)
    {
        return;
    }

    if (TickCount < TimeStep)
    {
        ExportRelativeHandDatasToCSV();
        TickCount++;

        //메시지 내용, 메시지 키, 출력 시간(초), 텍스트 색상 지정
        //FString Message = TEXT("Hand Data Recording - %d   /   %d", TickCount, TimeStep);
        FString Message = FString::Printf(TEXT("Hand Data Recording  -  %d / %d"), TickCount, TimeStep);
        FColor TextColor = FColor::Red;
        float DisplayTime = -1.0f;

        // 메시지 출력 (키는 0부터 9999까지 임의로 설정 가능)
        GEngine->AddOnScreenDebugMessage(-1, DisplayTime, TextColor, Message);
    }
    else if (TickCount == TimeStep)
    {
        TickCount = 9999;

        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
            {
                TickCount = 0;
                LearningSampleCount++;

                 //메시지 내용, 메시지 키, 출력 시간(초), 텍스트 색상 지정
                FString Message = TEXT("Repeat Export Hand Data!!!!");
                FColor TextColor = FColor::Green;
                float DisplayTime = 1.0f; 

                // 메시지 출력 (키는 0부터 9999까지 임의로 설정 가능)
                GEngine->AddOnScreenDebugMessage(-1, DisplayTime, TextColor, Message);
            }, 3.0f, false);
    }

    //if (TickCount < 2000)
    //{
    //    //TArray<UJointMeshComponent*> OwnerHandJointMeshes = OwnerPawn->GetHandJointMeshes();
    //    //ExportHandDatasToCSV(OwnerRightHand, HandJointMeshes, HandDataLabel);
    //    ExportRelativeHandDatasToCSV();

    //    TickCount++;

    //    if (TickCount == 2000)
    //    {
    //        // 메시지 내용, 메시지 키, 출력 시간(초), 텍스트 색상 지정
    //        FString Message = TEXT("End Data Cap!");
    //        FColor TextColor = FColor::Green;
    //        float DisplayTime = 1.0f; // 5초 동안 표시

    //        // 메시지 출력 (키는 0부터 9999까지 임의로 설정 가능)
    //        GEngine->AddOnScreenDebugMessage(-1, DisplayTime, TextColor, Message);
    //    }
    //}
}


void UHandTrackingDataComponent::CalculateRelativeJoint()
{
    HandJointRelativeLocations.Empty();
    HandJointRelativeRotations.Empty();

    TArray<double> J;

    // StartIndex = NextIndex of RootWrist
    for (int i = 0; i < HandJointMeshes.Num(); i++)
    {
        if (i == 0)
        {
            UCameraComponent* OwnerCameraComponent = OwnerPawn->GetComponentByClass<UCameraComponent>();
            FVector CameraLocation = OwnerCameraComponent->GetComponentLocation();
            FVector WristRootJointLocation = HandJointMeshes[0]->GetComponentLocation();

            FVector RelativeLocation = WristRootJointLocation - CameraLocation;
            HandJointRelativeLocations.Add(RelativeLocation);


            FQuat CameraQuat = OwnerCameraComponent->GetComponentQuat();
            FQuat WristRootJointQuat = HandJointMeshes[0]->GetComponentQuat();
            FQuat RelativeQuat = WristRootJointQuat * CameraQuat.Inverse();

            FRotator RelativeRotation = RelativeQuat.Rotator();
            HandJointRelativeRotations.Add(RelativeRotation);

            J.Add(RelativeRotation.Pitch);
            J.Add(RelativeRotation.Yaw);
            J.Add(RelativeRotation.Roll);
            J.Add(RelativeLocation.X);
            J.Add(RelativeLocation.Y);
            J.Add(RelativeLocation.Z);

            //DrawDebugLine(GetWorld(), CameraLocation, WristRootJointLocation, FColor::Green, false, -1.0f);
        }
        else if (i == 1 || i == 6 || i == 10 || i == 14 || i == 18)
        {
            FVector ParentJointLocation = HandJointMeshes[0]->GetComponentLocation();
            FVector ChildJointLocation = HandJointMeshes[i]->GetComponentLocation();
            FVector RelativeLocation = ChildJointLocation - ParentJointLocation;
            HandJointRelativeLocations.Add(RelativeLocation);

            FQuat ParentJointQuat = HandJointMeshes[0]->GetComponentQuat();
            FQuat ChildJointQuat = HandJointMeshes[i]->GetComponentQuat();

            FQuat RelativeQuat = ChildJointQuat * ParentJointQuat.Inverse();
            FRotator RelativeRotation = RelativeQuat.Rotator();
            HandJointRelativeRotations.Add(RelativeRotation);

            
            J.Add(RelativeRotation.Pitch);
            J.Add(RelativeRotation.Yaw);
            J.Add(RelativeRotation.Roll);
            J.Add(RelativeLocation.X);
            J.Add(RelativeLocation.Y);
            J.Add(RelativeLocation.Z);

            DrawDebugLine(GetWorld(), ParentJointLocation, ChildJointLocation, FColor::Green, false, -1.0f);

            //UE_LOG(LogTemp, Display, TEXT("%f,%f,%f   %f,%f,%f"), ParentJointLocation.X, ParentJointLocation.Y, ParentJointLocation.Z, ChildJointLocation.X, ChildJointLocation.Y, ChildJointLocation.Z);
        }
        else
        {
            FVector ParentJointLocation = HandJointMeshes[i - 1]->GetComponentLocation();
            FVector ChildJointLocation = HandJointMeshes[i]->GetComponentLocation();
            FVector RelativeLocation = ChildJointLocation - ParentJointLocation;
            HandJointRelativeLocations.Add(RelativeLocation);

            FQuat ParentJointQuat = HandJointMeshes[i - 1]->GetComponentQuat();
            FQuat ChildJointQuat = HandJointMeshes[i]->GetComponentQuat();

            FQuat RelativeQuat = ChildJointQuat * ParentJointQuat.Inverse();
            FRotator RelativeRotation = RelativeQuat.Rotator();
            HandJointRelativeRotations.Add(RelativeRotation);

            J.Add(RelativeRotation.Pitch);
            J.Add(RelativeRotation.Yaw);
            J.Add(RelativeRotation.Roll);
            J.Add(RelativeLocation.X);
            J.Add(RelativeLocation.Y);
            J.Add(RelativeLocation.Z);

            DrawDebugLine(GetWorld(), ParentJointLocation, ChildJointLocation, FColor::Green, false, -1.0f);
        }
    }

    OwnerPawn->JointSequenceData.Enqueue(J);
    OwnerPawn->QueueCount++;
    if (OwnerPawn->QueueCount > 80)
    {
        OwnerPawn->JointSequenceData.Pop();
        OwnerPawn->QueueCount--;
    }
}



