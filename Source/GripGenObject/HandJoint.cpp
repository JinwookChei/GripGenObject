// Fill out your copyright notice in the Description page of Project Settings.


#include "HandJoint.h"
#include "JointMeshComponent.h"
#include "CommonTypes.h"

// Sets default values for this component's properties
UHandJoint::UHandJoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHandJoint::BeginPlay()
{
	Super::BeginPlay();
	// Wrist Root
	Wrist_Root = NewObject<UJointMeshComponent>(this, FName(TEXT("Wrist Root")));
	Wrist_Root->SetHandJointType(EHandJointType::WristRoot);
	Wrist_Root->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	//Wrist_Root->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));
	

	// Thumb joints
	Thumb0 = NewObject<UJointMeshComponent>(this, FName(TEXT("Thumb0")));
	Thumb0->SetHandJointType(EHandJointType::Thumb0);
	Thumb0->AttachToComponent(Wrist_Root, FAttachmentTransformRules::KeepRelativeTransform);
	//Thumb0->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Thumb1 = NewObject<UJointMeshComponent>(this, FName(TEXT("Thumb1")));
	Thumb1->SetHandJointType(EHandJointType::Thumb1);
	Thumb1->AttachToComponent(Thumb0, FAttachmentTransformRules::KeepRelativeTransform);
	//Thumb1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Thumb2 = NewObject<UJointMeshComponent>(this, FName(TEXT("Thumb2")));
	Thumb2->SetHandJointType(EHandJointType::Thumb2);
	Thumb2->AttachToComponent(Thumb1, FAttachmentTransformRules::KeepRelativeTransform);
	//Thumb2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Thumb3 = NewObject<UJointMeshComponent>(this, FName(TEXT("Thumb3")));
	Thumb3->SetHandJointType(EHandJointType::Thumb3);
	Thumb3->AttachToComponent(Thumb2, FAttachmentTransformRules::KeepRelativeTransform);
	//Thumb3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Thumb_Tip = NewObject<UJointMeshComponent>(this, FName(TEXT("Thumb Tip")));
	Thumb_Tip->SetHandJointType(EHandJointType::Thumb_Tip);
	Thumb_Tip->AttachToComponent(Thumb3, FAttachmentTransformRules::KeepRelativeTransform);
	//Thumb_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Index joints
	Index1 = NewObject<UJointMeshComponent>(this, FName(TEXT("Index1")));
	Index1->SetHandJointType(EHandJointType::Index1);
	Index1->AttachToComponent(Wrist_Root, FAttachmentTransformRules::KeepRelativeTransform);
	//Index1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Index2 = NewObject<UJointMeshComponent>(this, FName(TEXT("Index2")));
	Index2->SetHandJointType(EHandJointType::Index2);
	Index2->AttachToComponent(Index1, FAttachmentTransformRules::KeepRelativeTransform);
	//Index2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Index3 = NewObject<UJointMeshComponent>(this, FName(TEXT("Index3")));
	Index3->SetHandJointType(EHandJointType::Index3);
	Index3->AttachToComponent(Index2, FAttachmentTransformRules::KeepRelativeTransform);
	//Index3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Index_Tip = NewObject<UJointMeshComponent>(this, FName(TEXT("Index Tip")));
	Index_Tip->SetHandJointType(EHandJointType::Index_Tip);
	Index_Tip->AttachToComponent(Index3, FAttachmentTransformRules::KeepRelativeTransform);
	//Index_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Middle joints
	Middle1 = NewObject<UJointMeshComponent>(this, FName(TEXT("Middle1")));
	Middle1->SetHandJointType(EHandJointType::Middle1);
	Middle1->AttachToComponent(Wrist_Root, FAttachmentTransformRules::KeepRelativeTransform);
	//Middle1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Middle2 = NewObject<UJointMeshComponent>(this, FName(TEXT("Middle2")));
	Middle2->SetHandJointType(EHandJointType::Middle2);
	Middle2->AttachToComponent(Middle1, FAttachmentTransformRules::KeepRelativeTransform);
	//Middle2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Middle3 = NewObject<UJointMeshComponent>(this, FName(TEXT("Middle3")));
	Middle3->SetHandJointType(EHandJointType::Middle3);
	Middle3->AttachToComponent(Middle2, FAttachmentTransformRules::KeepRelativeTransform);
	//Middle3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Middle_Tip = NewObject<UJointMeshComponent>(this, FName(TEXT("Middle Tip")));
	Middle_Tip->SetHandJointType(EHandJointType::Middle_Tip);
	Middle_Tip->AttachToComponent(Middle3, FAttachmentTransformRules::KeepRelativeTransform);
	//Middle_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Ring joints
	Ring1 = NewObject<UJointMeshComponent>(this, FName(TEXT("Ring1")));
	Ring1->SetHandJointType(EHandJointType::Ring1);
	Ring1->AttachToComponent(Wrist_Root, FAttachmentTransformRules::KeepRelativeTransform);
	//Ring1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Ring2 = NewObject<UJointMeshComponent>(this, FName(TEXT("Ring2")));
	Ring2->SetHandJointType(EHandJointType::Ring2);
	Ring2->AttachToComponent(Ring1, FAttachmentTransformRules::KeepRelativeTransform);
	//Ring2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Ring3 = NewObject<UJointMeshComponent>(this, FName(TEXT("Ring3")));
	Ring3->SetHandJointType(EHandJointType::Ring3);
	Ring3->AttachToComponent(Ring2, FAttachmentTransformRules::KeepRelativeTransform);
	//Ring3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Ring_Tip = NewObject<UJointMeshComponent>(this, FName(TEXT("Ring Tip")));
	Ring_Tip->SetHandJointType(EHandJointType::Ring_Tip);
	Ring_Tip->AttachToComponent(Ring3, FAttachmentTransformRules::KeepRelativeTransform);
	//Ring_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	// Pinky joints
	Pinky0 = NewObject<UJointMeshComponent>(this, FName(TEXT("Pinky0")));
	Pinky0->SetHandJointType(EHandJointType::Pinky0);
	Pinky0->AttachToComponent(Wrist_Root, FAttachmentTransformRules::KeepRelativeTransform);
	//Pinky0->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Pinky1 = NewObject<UJointMeshComponent>(this, FName(TEXT("Pinky1")));
	Pinky1->SetHandJointType(EHandJointType::Pinky1);
	Pinky1->AttachToComponent(Pinky0, FAttachmentTransformRules::KeepRelativeTransform);
	//Pinky1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Pinky2 = NewObject<UJointMeshComponent>(this, FName(TEXT("Pinky2")));
	Pinky2->SetHandJointType(EHandJointType::Pinky2);
	Pinky2->AttachToComponent(Pinky1, FAttachmentTransformRules::KeepRelativeTransform);
	//Pinky2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Pinky3 = NewObject<UJointMeshComponent>(this, FName(TEXT("Pinky3")));
	Pinky3->SetHandJointType(EHandJointType::Pinky3);
	Pinky3->AttachToComponent(Pinky2, FAttachmentTransformRules::KeepRelativeTransform);
	//Pinky3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	Pinky_Tip = NewObject<UJointMeshComponent>(this, FName(TEXT("Pinky Tip")));
	Pinky_Tip->SetHandJointType(EHandJointType::Pinky_Tip);
	Pinky_Tip->AttachToComponent(Pinky3, FAttachmentTransformRules::KeepRelativeTransform);
	//Pinky_Tip->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	JointArray = {
	Wrist_Root, Thumb0, Thumb1, Thumb2, Thumb3, Thumb_Tip,
	Index1, Index2, Index3, Index_Tip,
	Middle1, Middle2, Middle3, Middle_Tip,
	Ring1, Ring2, Ring3, Ring_Tip,
	Pinky0, Pinky1, Pinky2, Pinky3, Pinky_Tip
	};
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


