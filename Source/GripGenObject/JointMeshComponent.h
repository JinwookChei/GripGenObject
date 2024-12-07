// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "CommonTypes.h"
#include "JointMeshComponent.generated.h"


/**
 * 
 */

UCLASS()
class GRIPGENOBJECT_API UJointMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
    EHandJointType HandJointType;

public:
    void SetHandJointType(EHandJointType _HandJointType);
	
    EHandJointType GetHandJointType();
};
