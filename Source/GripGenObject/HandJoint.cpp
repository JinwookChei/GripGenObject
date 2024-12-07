// Fill out your copyright notice in the Description page of Project Settings.


#include "HandJoint.h"
#include "JointMeshComponent.h"

// Sets default values for this component's properties
UHandJoint::UHandJoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	// StaticMeshComponent�� �����ϰ� SceneComponent�� ������ ����
	Wrist_Root = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Wrist Root"));
	Wrist_Root->SetHandJointType(EHandJointType::WristRoot);
	Wrist_Root->SetupAttachment(this); // �� ������Ʈ�� �θ�� ����
	Wrist_Root->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Thumb joints
	Thumb0 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb0"));
	Thumb0->SetHandJointType(EHandJointType::Thumb0);
	Thumb0->SetupAttachment(Wrist_Root);
	Thumb0->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Thumb1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb1"));
	Thumb1->SetHandJointType(EHandJointType::Thumb1);
	Thumb1->SetupAttachment(Thumb0);
	Thumb1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Thumb2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb2"));
	Thumb2->SetHandJointType(EHandJointType::Thumb2);
	Thumb2->SetupAttachment(Thumb1);
	Thumb2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Thumb3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb3"));
	Thumb3->SetHandJointType(EHandJointType::Thumb3);
	Thumb3->SetupAttachment(Thumb2);
	Thumb3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Thumb_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Thumb Tip"));
	Thumb_Tip->SetHandJointType(EHandJointType::Thumb_Tip);
	Thumb_Tip->SetupAttachment(Thumb3);
	Thumb_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Index joints
	Index1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Index1"));
	Index1->SetHandJointType(EHandJointType::Index1);
	Index1->SetupAttachment(Wrist_Root);
	Index1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Index2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Index2"));
	Index2->SetHandJointType(EHandJointType::Index2);
	Index2->SetupAttachment(Index1);
	Index2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Index3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Index3"));
	Index3->SetHandJointType(EHandJointType::Index3);
	Index3->SetupAttachment(Index2);
	Index3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Index_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Index Tip"));
	Index_Tip->SetHandJointType(EHandJointType::Index_Tip);
	Index_Tip->SetupAttachment(Index3);
	Index_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Middle joints
	Middle1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Middle1"));
	Middle1->SetHandJointType(EHandJointType::Middle1);
	Middle1->SetupAttachment(Wrist_Root);
	Middle1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Middle2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Middle2"));
	Middle2->SetHandJointType(EHandJointType::Middle2);
	Middle2->SetupAttachment(Middle1);
	Middle2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Middle3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Middle3"));
	Middle3->SetHandJointType(EHandJointType::Middle3);
	Middle3->SetupAttachment(Middle2);
	Middle3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Middle_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Middle Tip"));
	Middle_Tip->SetHandJointType(EHandJointType::Middle_Tip);
	Middle_Tip->SetupAttachment(Middle3);
	Middle_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Ring joints
	Ring1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Ring1"));
	Ring1->SetHandJointType(EHandJointType::Ring1);
	Ring1->SetupAttachment(Wrist_Root);
	Ring1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Ring2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Ring2"));
	Ring2->SetHandJointType(EHandJointType::Ring2);
	Ring2->SetupAttachment(Ring1);
	Ring2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Ring3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Ring3"));
	Ring3->SetHandJointType(EHandJointType::Ring3);
	Ring3->SetupAttachment(Ring2);
	Ring3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Ring_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Ring Tip"));
	Ring_Tip->SetHandJointType(EHandJointType::Ring_Tip);
	Ring_Tip->SetupAttachment(Ring3);
	Ring_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Pinky joints
	Pinky0 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky0"));
	Pinky0->SetHandJointType(EHandJointType::Pinky0);
	Pinky0->SetupAttachment(Wrist_Root);
	Pinky0->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Pinky1 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky1"));
	Pinky1->SetHandJointType(EHandJointType::Pinky1);
	Pinky1->SetupAttachment(Pinky0);
	Pinky1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Pinky2 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky2"));
	Pinky2->SetHandJointType(EHandJointType::Pinky2);
	Pinky2->SetupAttachment(Pinky1);
	Pinky2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Pinky3 = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky3"));
	Pinky3->SetHandJointType(EHandJointType::Pinky3);
	Pinky3->SetupAttachment(Pinky2);
	Pinky3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Pinky_Tip = CreateDefaultSubobject<UJointMeshComponent>(TEXT("Pinky Tip"));
	Pinky_Tip->SetHandJointType(EHandJointType::Pinky_Tip);
	Pinky_Tip->SetupAttachment(Pinky3);
	Pinky_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	JointArray = {
	Wrist_Root, Thumb0, Thumb1, Thumb2, Thumb3, Thumb_Tip,
	Index1, Index2, Index3, Index_Tip,
	Middle1, Middle2, Middle3, Middle_Tip,
	Ring1, Ring2, Ring3, Ring_Tip,
	Pinky0, Pinky1, Pinky2, Pinky3, Pinky_Tip
	};
}


// Called when the game starts
void UHandJoint::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//for (auto& i : JointArray)
	//{
	//	UE_LOG(LogTemp, Display, TEXT("%s"), *i->GetName());
	//}
	
}


// Called every frame
void UHandJoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UHandJoint::GetJointCount()
{
	return JointCount;
}

TArray<UJointMeshComponent*> UHandJoint::GetJointArray()
{
	return JointArray;
}

FVector UHandJoint::GetWristRootWorldLocation()
{
	return Wrist_Root->GetComponentLocation();
}

FRotator UHandJoint::GetWristRootWorldRotation()
{
	return Wrist_Root->GetComponentRotation();
}

