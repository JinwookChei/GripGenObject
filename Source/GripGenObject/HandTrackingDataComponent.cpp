// Fill out your copyright notice in the Description page of Project Settings.


#include "HandTrackingDataComponent.h"
#include "VRPawn.h"
#include "OculusXRHandComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "JointMeshComponent.h"
        


// Sets default values for this component's properties
UHandTrackingDataComponent::UHandTrackingDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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
    }

    TickCnt = 9999;
}


// Called every frame
void UHandTrackingDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    ExportHandDatasToCSV_Loop();
}

void UHandTrackingDataComponent::StartWriteCSVData(EHandDataLabel _HandDataLabel)
{
    HandDataLabel = _HandDataLabel;
    Initialize_CSVData();
}

void UHandTrackingDataComponent::Initialize_CSVData()
{
    TickCnt = 0;

    //Filename = FPaths::ProjectDir() + TEXT("JointData.csv");

    // 저장 폴더 경로 지정 (Saved/HandTrackingData)
    FString Directory = FPaths::Combine(FPaths::ProjectDir(), TEXT("HandTrackingData"));

    // 디렉터리 생성 (없는 경우)
    if (!IFileManager::Get().DirectoryExists(*Directory))
    {
        IFileManager::Get().MakeDirectory(*Directory, true);
    }

    // 파일 경로 지정
    Filename = FPaths::Combine(Directory, TEXT("JointData.csv"));

    // Initialize the CSV data string with the header (optional, but useful for clarity)
    CSVData = TEXT("WristRoot_Pitch,WristRoot_Yaw,WristRoot_Roll,WristRoot_X,WristRoot_Y,WristRoot_Z,");

    CSVData += TEXT("Thumb0_Rotation_Pitch,Thumb0_Rotation_Yaw,Thumb0_Rotation_Roll,Thumb0_Location_X,Thumb0_Location_Y,Thumb0_Location_Z,");
    CSVData += TEXT("Thumb1_Rotation_Pitch,Thumb1_Rotation_Yaw,Thumb1_Rotation_Roll,Thumb1_Location_X,Thumb1_Location_Y,Thumb1_Location_Z,");
    CSVData += TEXT("Thumb2_Rotation_Pitch,Thumb2_Rotation_Yaw,Thumb2_Rotation_Roll,Thumb2_Location_X,Thumb2_Location_Y,Thumb2_Location_Z,");
    CSVData += TEXT("Thumb3_Rotation_Pitch,Thumb3_Rotation_Yaw,Thumb3_Rotation_Roll,Thumb3_Location_X,Thumb3_Location_Y,Thumb3_Location_Z,");
    CSVData += TEXT("Thumb_Tip_Rotation_Pitch,Thumb_Tip_Rotation_Yaw,Thumb_Tip_Rotation_Roll,Thumb_Tip_Location_X,Thumb_Tip_Location_Y,Thumb_Tip_Location_Z,");

    CSVData += TEXT("Index1_Rotation_Pitch,Index1_Rotation_Yaw,Index1_Rotation_Roll,Index1_Location_X,Index1_Location_Y,Index1_Location_Z,");
    CSVData += TEXT("Index2_Rotation_Pitch,Index2_Rotation_Yaw,Index2_Rotation_Roll,Index2_Location_X,Index2_Location_Y,Index2_Location_Z,");
    CSVData += TEXT("Index3_Rotation_Pitch,Index3_Rotation_Yaw,Index3_Rotation_Roll,Index3_Location_X,Index3_Location_Y,Index3_Location_Z,");
    CSVData += TEXT("Index_Tip_Rotation_Pitch,Index_Tip_Rotation_Yaw,Index_Tip_Rotation_Roll,Index_Tip_Location_X,Index_Tip_Location_Y,Index_Tip_Location_Z,");

    CSVData += TEXT("Middle1_Rotation_Pitch,Middle1_Rotation_Yaw,Middle1_Rotation_Roll,Middle1_Location_X,Middle1_Location_Y,Middle1_Location_Z,");
    CSVData += TEXT("Middle2_Rotation_Pitch,Middle2_Rotation_Yaw,Middle2_Rotation_Roll,Middle2_Location_X,Middle2_Location_Y,Middle2_Location_Z,");
    CSVData += TEXT("Middle3_Rotation_Pitch,Middle3_Rotation_Yaw,Middle3_Rotation_Roll,Middle3_Location_X,Middle3_Location_Y,Middle3_Location_Z,");
    CSVData += TEXT("Middle_Tip_Rotation_Pitch,Middle_Tip_Rotation_Yaw,Middle_Tip_Rotation_Roll,Middle_Tip_Location_X,Middle_Tip_Location_Y,Middle_Tip_Location_Z,");

    CSVData += TEXT("Ring1_Rotation_Pitch,Ring1_Rotation_Yaw,Ring1_Rotation_Roll,Ring1_Location_X,Ring1_Location_Y,Ring1_Location_Z,");
    CSVData += TEXT("Ring2_Rotation_Pitch,Ring2_Rotation_Yaw,Ring2_Rotation_Roll,Ring2_Location_X,Ring2_Location_Y,Ring2_Location_Z,");
    CSVData += TEXT("Ring3_Rotation_Pitch,Ring3_Rotation_Yaw,Ring3_Rotation_Roll,Ring3_Location_X,Ring3_Location_Y,Ring3_Location_Z,");
    CSVData += TEXT("Ring_Tip_Rotation_Pitch,Ring_Tip_Rotation_Yaw,Ring_Tip_Rotation_Roll,Ring_Tip_Location_X,Ring_Tip_Location_Y,Ring_Tip_Location_Z,");

    CSVData += TEXT("Pinky0_Rotation_Pitch,Pinky0_Rotation_Yaw,Pinky0_Rotation_Roll,Pinky0_Location_X,Pinky0_Location_Y,Pinky0_Location_Z,");
    CSVData += TEXT("Pinky1_Rotation_Pitch,Pinky1_Rotation_Yaw,Pinky1_Rotation_Roll,Pinky1_Location_X,Pinky1_Location_Y,Pinky1_Location_Z,");
    CSVData += TEXT("Pinky2_Rotation_Pitch,Pinky2_Rotation_Yaw,Pinky2_Rotation_Roll,Pinky2_Location_X,Pinky2_Location_Y,Pinky2_Location_Z,");
    CSVData += TEXT("Pinky3_Rotation_Pitch,Pinky3_Rotation_Yaw,Pinky3_Rotation_Roll,Pinky3_Location_X,Pinky3_Location_Y,Pinky3_Location_Z,");
    CSVData += TEXT("Pinky_Tip_Rotation_Pitch,Pinky_Tip_Rotation_Yaw,Pinky_Tip_Rotation_Roll,Pinky_Tip_Location_X,Pinky_Tip_Location_Y,Pinky_Tip_Location_Z,");
    
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

            JointLocation = CameraLocation - RightHandLocation;
            FQuat RelativeQuat = RightHandQuat* CameraQuat.Inverse();
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

void UHandTrackingDataComponent::ExportHandDatasToCSV_Loop()
{
    if (TickCnt < 2000)
    {
        TArray<UJointMeshComponent*> OwnerHandJointMeshes = OwnerPawn->GetHandJointMeshes();
        ExportHandDatasToCSV(OwnerRightHand, OwnerHandJointMeshes, HandDataLabel);
        TickCnt++;

        if (TickCnt == 2000)
        {
            // 메시지 내용, 메시지 키, 출력 시간(초), 텍스트 색상 지정
            FString Message = TEXT("End Data Cap!");
            FColor TextColor = FColor::Green;
            float DisplayTime = 5.0f; // 5초 동안 표시

            // 메시지 출력 (키는 0부터 9999까지 임의로 설정 가능)
            GEngine->AddOnScreenDebugMessage(-1, DisplayTime, TextColor, Message);
        }
    }
}

