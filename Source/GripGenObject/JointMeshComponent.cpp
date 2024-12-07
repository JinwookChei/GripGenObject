// Fill out your copyright notice in the Description page of Project Settings.


#include "JointMeshComponent.h"

void UJointMeshComponent::SetHandJointType(EHandJointType _HandJointType)
{
	HandJointType = _HandJointType;
}

EHandJointType UJointMeshComponent::GetHandJointType()
{
	return HandJointType;
}
