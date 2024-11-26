// Fill out your copyright notice in the Description page of Project Settings.


#include "JointMeshComponent.h"

void UJointMeshComponent::SetHandJointType(EHandJoint _HandJointType)
{
	HandJointType = _HandJointType;
}

EHandJoint UJointMeshComponent::GetHandJointType()
{
	return HandJointType;
}
