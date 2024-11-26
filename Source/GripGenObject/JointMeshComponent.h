// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "JointMeshComponent.generated.h"

/**
 * 
 */
UENUM(BlueprintType) // Blueprint에서 사용 가능하도록 선언
enum class EHandJoint : uint8
{
    WristRoot UMETA(DisplayName = "Wrist Root"),

    Thumb0 UMETA(DisplayName = "Thumb0"),
    Thumb1 UMETA(DisplayName = "Thumb1"),
    Thumb2 UMETA(DisplayName = "Thumb2"),
    Thumb3 UMETA(DisplayName = "Thumb3"),

    Index1 UMETA(DisplayName = "Index1"),
    Index2 UMETA(DisplayName = "Index2"),
    Index3 UMETA(DisplayName = "Index3"),

    Middle1 UMETA(DisplayName = "Middle1"),
    Middle2 UMETA(DisplayName = "Middle2"),
    Middle3 UMETA(DisplayName = "Middle3"),

    Ring1 UMETA(DisplayName = "Ring1"),
    Ring2 UMETA(DisplayName = "Ring2"),
    Ring3 UMETA(DisplayName = "Ring3"),

    Pinky0 UMETA(DisplayName = "Pinky0"),
    Pinky1 UMETA(DisplayName = "Pinky1"),
    Pinky2 UMETA(DisplayName = "Pinky2"),
    Pinky3 UMETA(DisplayName = "Pinky3"),


    Thumb_Tip UMETA(DisplayName = "Thumb Tip"),
    Index_Tip UMETA(DisplayName = "Index Tip"),
    Middle_Tip UMETA(DisplayName = "Middle Tip"),
    Ring_Tip UMETA(DisplayName = "Ring Tip"),
    Pinky_Tip UMETA(DisplayName = "Pinky Tip")
};


UCLASS()
class GRIPGENOBJECT_API UJointMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
    EHandJoint HandJointType;

public:
    void SetHandJointType(EHandJoint _HandJointType);
	
    EHandJoint GetHandJointType();
};
